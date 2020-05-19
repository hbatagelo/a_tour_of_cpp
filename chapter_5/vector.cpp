#include "vector.hpp"
#include <algorithm>
#include <bits/c++config.h>
#include <iostream>

Vector::Vector(std::size_t s) {
  if (s < 0) {
    throw std::length_error{"Vector constructor: negative size"};
  }
  elem = std::make_unique<double[]>(s); // RAII
  sz = s;
  std::cout << "Ordinary constructor\n";
}

Vector::Vector(std::initializer_list<double> lst)
    : elem{std::make_unique<double[]>(lst.size())}, sz{lst.size()} {
  std::copy(lst.begin(), lst.end(), elem.get());
  std::cout << "Initializer list constructor\n";
}

Vector::Vector(const Vector &other)
    : elem{std::make_unique<double[]>(other.size())}, sz{other.sz} {
  std::copy(other.elem.get(), other.elem.get() + other.size(), elem.get());
  std::cout << "Copy constructor\n";
}

Vector::Vector(Vector &&other) noexcept
    : elem{std::move(other.elem)}, sz{other.sz} {
  other.sz = 0;
  std::cout << "Move constructor\n";
}

Vector::~Vector() { std::cout << "Destructor\n"; }

Vector &Vector::operator=(const Vector &other) {
  if (&other == this) {
    return *this;
  }
  elem = std::make_unique<double[]>(other.size());
  std::copy(other.elem.get(), other.elem.get() + other.size(), elem.get());
  sz = other.size();
  std::cout << "Copy assignment\n";
  return *this;
}

Vector &Vector::operator=(Vector &&other) noexcept {
  elem = std::move(other.elem);
  sz = other.size();
  other.sz = 0;
  std::cout << "Move assignment\n";
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

Vector operator+(const Vector &a, const Vector &b) {
  if (a.size() != b.size()) {
    throw Vector_size_mismatch{};
  }

  Vector res(a.size());
  for (std::size_t i = 0; i < a.size(); ++i) {
    res[i] = a[i] + b[i];
  }

  // Copy is elided (NRVO)
  return res;

  // A move will occur below. NRVO (lvalue) and RVO (prvalue) cannot be used
  // here because the result of std::move is an xvalue.

  // return std::move(res);
}

std::size_t Vector::size() const { return sz; }

void Vector::push_back([[maybe_unused]] double x) {
  // To be implemented
}