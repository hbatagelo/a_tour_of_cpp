#include "complex.hpp"

void f(complex z) {
  complex a{2.3};
  complex b{complex{1} / a};
  complex c{a + z * complex{1, 2.3}};

  if (c != b) {
    c = -(b / a) + complex{2} * b;
  }
}

int main() {}