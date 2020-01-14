#include <iostream>

int main() {
  int i = @expression("10+12");
  std::cout << i << std::endl; // Outputs 22
}
