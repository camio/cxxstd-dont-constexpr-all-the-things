#include <cmath>
#include <iostream>
double f() { return sin(3) + sin(5); }

// outputs -0.817804 at compile time
@meta std::cout << f() << std::endl;
