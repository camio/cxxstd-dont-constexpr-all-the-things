#include <iostream>

@meta int j = 0;

@mauto f(int i) {
  @meta ++j;
  return i*i*j;
}

int main()
{
  int x = f(100); // Produces in code: int x = 100*100*0;
  int y = f(100); // Produces in code: int y = 100*100*1;
  std::cout << x << std::endl;
  std::cout << y << std::endl;
}
