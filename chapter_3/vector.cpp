#include "vector.hpp"

Vector::Vector(int s) {
  if (s < 0) {
    throw std::length_error{"Vector constructor: negative size"};
  }
  elem = std::make_unique<double>(s);
  sz = s;
}

double &Vector::operator[](int i) {
  if (i < 0 || size() <= i) {
    throw std::out_of_range{"Vector::operator[]: out of range"};
  }
  return elem.get()[i];
}

int Vector::size() const { return sz; }