#include "vector.hpp"
#include <complex>
#include <iostream>
#include <list>
#include <tuple>

// A function template
template <typename Sequence, typename Value>
Value sum(const Sequence &s, Value v) {
  for (auto &x : s) {
    v += x;
  }
  return v;
}

std::tuple<int, double, double, std::complex<double>>
user(Vector<int> &vi, std::list<double> &ld,
     std::vector<std::complex<double>> &vc) {
  // The sum of a vector of ints (add ints)
  int x = sum(vi, 0);
  // The sum of a vector of ints (add doubles)
  double d = sum(vi, 0.0);
  // The sum of a list of doubles
  double dd = sum(ld, 0.0);
  // The sum of a vector of complex<double>s
  auto z = sum(vc, std::complex{0.0, 0.0});

  return {x, d, dd, z};
}

int main() {
  Vector<int> vi{1, 2, 3};
  std::list<double> ld{5, 6, 7};
  std::vector<std::complex<double>> vc{{1, 2}, {1, 0}, {2, 0}};

  auto [v1, v2, v3, v4] = user(vi, ld, vc);
  std::cout << v1 << '\n';
  std::cout << v2 << '\n';
  std::cout << v3 << '\n';
  std::cout << v4 << '\n';
}
