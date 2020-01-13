#include <cstring>
#include <vector>

// Compiles fine
constexpr int plus(int a, int b) {
  return a + b;
}

//// ERROR (maybe)
//constexpr void fast_zero(std::vector<int> &vec) {
//  std::memset(vec.data(), 0, vec.size() * sizeof(int));
////  return;
////  int a[5] {1,2,3,4,5};
////  std::memset(a, 0, sizeof a);
////  std::vector<int> vec2;
//}

// OK (w/ clang, but not g++)
constexpr void fast_zero2(std::vector<int> &vec) {
  if(vec.size()) std::memset(vec.data(), 0, vec.size() * sizeof(int));
}

constexpr void fast_zero3(std::vector<int> &vec) {
  for(std::ptrdiff_t i = 0; i < vec.size(); ++i)
    vec[i] = 0;
}

constexpr void fast_zero4(std::vector<int> &vec) {
  if( std::is_constant_evaluated() )
    for(std::ptrdiff_t i = 0; i < vec.size(); ++i)
      vec[i] = 0;
  else
    std::memset(vec.data(), 0, vec.size() * sizeof(int));
}

consteval int f(int const &p) { return p; }

consteval int g(int const &p) {
  return f(p); // Okay (in consteval function).
}

void h()
{
    int r = f(42); // Okay
    int s = f(r); // Error: Must produce a constant

    int x = g(42); // Okay
    int y = g(x); // Error: not a constant.
}


//void f()
//{
//    consteval std::vector<int> vec;
//}
