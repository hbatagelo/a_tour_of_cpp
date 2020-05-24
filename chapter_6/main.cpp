#include <iostream>
#include <list>
#include <string>
#include "vector.hpp"

template <typename T, int N>
struct Buffer {
  using value_type = T;
  constexpr std::size_t size() { return N; }

 private:
  T value[N];
};

// A function template
template <typename Sequence, typename Value>
Value sum(const Sequence& s, Value v) {
  for (auto x : s) {
    v += x;
  }
  return v;
}

int main() {
  using namespace std::string_literals;
  Vector vs2{"abc"s, "def"s, "ghi"s};
  for (auto& s : vs2) {
    std::cout << s << '\n';
  }

  // Global buffer of characters (statically allocated)
  Buffer<char, 1024> glob{};
  std::cout << glob.size() << '\n';

  // Template argument deduction
  std::pair<int, double> p1 = {1, 5.2};
  auto p2 = std::make_pair(1, 5.2);
  std::pair p3 = {1, 5.2};  // C++17
  std::cout << p1.first << p2.first << p3.first << '\n';

  Vector v1{1, 2, 3};  // Type deduction
  Vector<int> v3(1);   // Here we need to be explicit
  Vector v2 = v1;      // Type deduction
  for (auto& s : v2) {
    std::cout << s << '\n';
  }
}
