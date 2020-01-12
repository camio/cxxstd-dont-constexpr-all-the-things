{-# LANGUAGE DeriveFunctor #-}
{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE FunctionalDependencies #-}
{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE TypeFamilies #-}
module Model where

import Control.Monad
import Data.Atomics.Counter
import System.IO
import Data.IORef
import Data.Bifunctor

data Received e a
    = ReceiveValue a
    | ReceiveError e
    | ReceiveDone
    deriving (Functor)
instance Bifunctor Received where
    second = fmap
    first _ (ReceiveValue v) = ReceiveValue v
    first f (ReceiveError e) = ReceiveError $ f e
    first _ ReceiveDone = ReceiveDone

class Sender s e a | s -> e, s -> a where
    connect :: s -> (Received e a -> IO ()) -> IO ()

data AnySender e a = forall s. (Sender s e a) => AnySender s
instance Sender (AnySender e a) e a where
    connect (AnySender s) = connect s

newtype WhenAll e a = WhenAll [AnySender e a]
when_all :: [AnySender e a] -> WhenAll e a
when_all = WhenAll

instance Sender (WhenAll e a) e [a] where
    connect (WhenAll senders) cont = do
        remainingCount <- newCounter $ length senders
        let
            createCorrespondingActions readResults sender = do
                pocket <- newIORef (Nothing :: Maybe (Received e a))
                return (readIORef pocket, sender `connect` hasReceived pocket readResults)
            hasReceived pocket readResults res = do
                writeIORef pocket (Just res)
                rem <- incrCounter (-1) remainingCount
                when (rem == 0) $ do
                    results <- readResults
                    cont $ ReceiveValue []  -- need to provide list of results here
            toFix pairs =
                let readResults = traverse fst pairs
                in traverse (createCorrespondingActions readResults) senders
        pairs <- fixIO toFix
        traverse snd pairs
        return ()

data Transform e a b = Transform (AnySender e a) (a -> b)
transform :: AnySender e a -> (a -> b) -> Transform e a b
transform = Transform

instance Sender (Transform e a b) e b where
    connect (Transform s f) cont = connect s $ (cont . fmap f)
