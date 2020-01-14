#include <iostream>

@meta int i = 3;

int main()
{
//    int j = i++; // ERROR. Same behavior as with consteval variables.
    int j = @meta i++; // ERROR. Same behavior as with consteval variables.
}
