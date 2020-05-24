#include "vector.hpp"

#include <algorithm>

Vector::Vector(std::size_t s) {
  if (s < 0) {
    throw std::length_error{"Vector constructor: negative size"};
  }
  elem = std::make_unique<double[]>(s);  // RAII
  sz = s;
}

double &Vector::operator[](std::size_t i) {
  if (i >= size()) {
    throw std::out_of_range{"Vector::operator[]: out of range"};
  }
  return elem.get()[i];
}

std::size_t Vector::size() const { return sz; }