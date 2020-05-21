#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <exception>
#include <memory>

template <typename T> class Vector {
public:
  explicit Vector(std::size_t s);
  Vector(std::initializer_list<T> lst); // Initialize with a list of doubles
  Vector(const Vector<T> &other);
  Vector(Vector<T> &&other) noexcept;
  ~Vector() = default;

  Vector &operator=(const Vector<T> &other);
  Vector &operator=(Vector<T> &&other) noexcept;

  T &operator[](std::size_t i);
  const T &operator[](std::size_t i) const;
  [[nodiscard]] std::size_t size() const;

  void push_back(T x); // Add element at end, increasing the size by one

private:
  std::unique_ptr<T[]> elem; // elem points to an array of sz doubles
  std::size_t sz;
};

class Vector_negative_size : std::exception {};
class Vector_size_mismatch : std::exception {};

template <typename T>
Vector<T> operator+(const Vector<T> &a, const Vector<T> &b);

template <typename T> Vector<T>::Vector(std::size_t s) {
  if (s < 0) {
    throw Vector_negative_size{};
  }
  elem = std::make_unique<T[]>(s); // RAII
  sz = s;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> lst)
    : elem{std::make_unique<T[]>(lst.size())}, sz{lst.size()} {
  std::copy(lst.begin(), lst.end(), elem.get());
}

template <typename T>
Vector<T>::Vector(const Vector &other)
    : elem{std::make_unique<T[]>(other.size())}, sz{other.sz} {
  std::copy(other.elem.get(), other.elem.get() + other.size(), elem.get());
}

template <typename T>
Vector<T>::Vector(Vector &&other) noexcept
    : elem{std::move(other.elem)}, sz{other.sz} {
  other.sz = 0;
}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
  if (&other == this) {
    return *this;
  }
  elem = std::make_unique<T[]>(other.size());
  std::copy(other.elem.get(), other.elem.get() + other.size(), elem.get());
  sz = other.size();
  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept {
  elem = std::move(other.elem);
  sz = other.size();
  other.sz = 0;
  return *this;
}

template <typename T> T &Vector<T>::operator[](std::size_t i) {
  if (i >= size()) {
    throw std::out_of_range{"Vector::operator[]"};
  }
  return elem.get()[i];
}

template <typename T> const T &Vector<T>::operator[](std::size_t i) const {
  if (i >= size()) {
    throw std::out_of_range{"Vector::operator[]"};
  }
  return elem.get()[i];
}

template <typename T>
Vector<T> operator+(const Vector<T> &a, const Vector<T> &b) {
  if (a.size() != b.size()) {
    throw Vector_size_mismatch{};
  }

  Vector<T> res(a.size());
  for (std::size_t i = 0; i < a.size(); ++i) {
    res[i] = a[i] + b[i];
  }

  return res;
}

template <typename T> std::size_t Vector<T>::size() const { return sz; }

template <typename T> void Vector<T>::push_back([[maybe_unused]] T x) {
  // To be implemented
}

//------------------------------------------------------------------------------
// Iterators (non-const)
template <typename T> T *begin(Vector<T> &x) {
  return x.size() ? &x[0] : nullptr;
}

template <typename T> T *end(Vector<T> &x) {
  return x.size() ? &x[0] + x.size() : nullptr;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Iterators (const)
template <typename T> const T *begin(const Vector<T> &x) {
  return x.size() ? &x[0] : nullptr;
}

template <typename T> const T *end(const Vector<T> &x) {
  return x.size() ? &x[0] + x.size() : nullptr;
}
//------------------------------------------------------------------------------

#endif