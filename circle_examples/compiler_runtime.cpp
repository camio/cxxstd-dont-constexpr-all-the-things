#include <iostream>

int i = 0;

int f() { return ++i; }

int main()
{
    std::cout << (@meta f()) << std::endl; // Outputs 1
    std::cout << (@meta f()) << std::endl; // Outputs 2
    std::cout << i << std::endl;           // Outputs 0
}
