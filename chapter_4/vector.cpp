
#include "vector.hpp"

#include <algorithm>
#include <iostream>

Vector::Vector(std::size_t s) {
  if (s < 0) {
    throw std::length_error{"Vector constructor: negative size"};
  }
  elem = std::make_unique<double[]>(s);  // RAII
  sz = s;
}

Vector::Vector(std::initializer_list<double> lst)
    : elem{std::make_unique<double[]>(lst.size())}, sz{lst.size()} {
  std::copy(lst.begin(), lst.end(), elem.get());
}

Vector::Vector(const Vector &other)
    : elem{std::make_unique<double[]>(other.size())}, sz{other.sz} {
  std::copy(other.elem.get(), other.elem.get() + other.size(), elem.get());
}

Vector::Vector(Vector &&other) noexcept
    : elem{std::move(other.elem)}, sz{other.sz} {
  other.sz = 0;
}

Vector &Vector::operator=(const Vector &other) {
  if (&other == this) {
    return *this;
  }
  elem = std::make_unique<double[]>(other.size());
  std::copy(other.elem.get(), other.elem.get() + other.size(), elem.get());
  sz = other.size();
  return *this;
}

Vector &Vector::operator=(Vector &&other) noexcept {
  elem = std::move(other.elem);
  sz = other.size();
  return *this;
}

double &Vector::operator[](std::size_t i) {
  if (i >= size()) {
    throw std::out_of_range{"Vector::operator[]: out of range"};
  }
  return elem.get()[i];
}

const double &Vector::operator[](std::size_t i) const {
  if (i >= size()) {
    throw std::out_of_range{"Vector::operator[]: out of range"};
  }
  return elem.get()[i];
}

std::size_t Vector::size() const { return sz; }

void Vector::push_back([[maybe_unused]] double x) {
  // To be implemented
}