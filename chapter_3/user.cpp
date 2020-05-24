#include <cmath>
#include <iostream>
#include <numeric>

#include "vector.hpp"

double sqrt_sum(Vector &v) {
  double sum{0};
  for (std::size_t i = 0; i != v.size(); ++i) {
    sum += std::sqrt(v[i]);  // sum of square
  }
  return sum;
}

void f(Vector &v) {
  try {  // Exceptions here are handled by the handler defined below
    v[v.size()] = 7;                  // Try to access beyond the end of v
  } catch (std::out_of_range &err) {  // oops: out_of_range error
    // ... handle range error ...
    std::cerr << "  what(): " << err.what() << '\n';
  }
}

void user(std::size_t sz) noexcept {
  Vector v(sz);
  // Fill v with 1, 2, 3, 4...
  // std::terminate() will be called because v[sz] will throw
  std::iota(&v[0], &v[sz], 1);
}

void test() {
  try {
    Vector v{10};
    std::cout << sqrt_sum(v) << '\n';
    f(v);
  } catch (std::length_error &err) {
    // Do something and rethrow
    std::cerr << "  what(): " << err.what() << '\n';
    throw;
  } catch (std::bad_alloc &err) {
    // Ouch! This program is not designed to handle memory exhaustion
    std::terminate();
  }
}

int main() {
  static_assert(4 <= sizeof(int), "integers are too small");
  test();
  user(10);
}