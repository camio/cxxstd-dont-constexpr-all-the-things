#include <iostream>

struct C { C(){ std::cout << "Hello World" << std::endl; } } c;
void f() { c; }
@meta f(); // Without this line, there is no "Hello World" at compile-time
           // Only entities that are ODR used require initialization.

int main() { f(); }
