#include "complex.hpp"

complex operator+(complex a, complex b) { return a += b; }
complex operator-(complex a, complex b) { return a -= b; }
complex operator-(complex a) { return {-a.real(), -a.imag()}; }
complex operator*(complex a, complex b) { return a *= b; }
complex operator/(complex a, complex b) { return a /= b; }

bool operator==(complex a, complex b) {
  return a.real() == b.real() && a.imag() == b.imag();
}

bool operator!=(complex a, complex b) { return !(a == b); }

complex &complex::operator*=([[maybe_unused]] complex a) {
  // To be implemented
  return *this;
}

complex &complex::operator/=([[maybe_unused]] complex a) {
  // To be implemented
  return *this;
}