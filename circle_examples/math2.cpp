#include <cmath>
#include <iostream>
double f() { return sin(3) + sin(5); }

int main() {
    constexpr double val = @meta f();
    std::cout << val << std::endl;
}
