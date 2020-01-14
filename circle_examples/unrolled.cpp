#include <iostream>

int main() {
  @meta for( int i = 0; i < 5; ++i ) {
    ++i;
    std::cout << "Unrolled Loop iteration" << (@meta i) << std::endl;
  }
}
