// port_a_vector.cpp
//
// PURPOSE: Demonstrate how to port a compile-time vector to a runtime vector.
//
// Description
// ===========
// Porting is the process by which we take a compile-time value and make it
// into a runtime value. In circle, the only way to do this is to manually
// build up an equivalent expression.

#include <iostream>
#include <vector>

@meta std::vector<int> ints {1, 2, 3, 4};

int main()
{
    std::cout << ints[0] << std::endl; // Okay

//    for(int i = 0; i < ints.size(); ++i ) {
//        std::cout << ints[i] << std::endl; // Error, cannot access 'i' at compile time.
//    }

    @meta for(int i = 0; i < ints.size(); ++i ) {
        std::cout << ints[i] << std::endl; // Okay
    }

//    std::vector<int> myInts2(ints); // ERROR: Only literal types can be ported

    std::vector<int> myInts{@pack_nontype(ints)...}; // Okay
    for(int i = 0; i < myInts.size(); ++i ) {
        std::cout << myInts[i] << std::endl;
    }

//    constexpr std::vector<int> myInts3{@pack_nontype(ints)...}; // ERROR: constexpr objects must have literal types.
}
