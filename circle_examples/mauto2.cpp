#include <iostream>

@mauto print(std::string s) {
  return std::cout << @string(s) << "=" << @@expression(s) << std::endl;
}

int main()
{
  int x = 12;
  print("x"); // outputs x=12
  print("x*x"); // outputs x*x=144
}
