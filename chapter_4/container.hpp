#include "vector.hpp"
#include <list>

class Container {
public:
  virtual const double &operator[](std::size_t) const = 0;
  [[nodiscard]] virtual std::size_t size() const = 0;
  virtual ~Container() = default;

protected:
  // Protected copy/move prevents polymorphic copy/move, which may lead to
  // slicing, and allows the concrete class to implicitly generate its
  // copy/move assignment operators.
  Container() = default;
  Container(const Container &) = default;                // Copy constructor
  Container(Container &&) noexcept = default;            // Move constructor
  Container &operator=(const Container &) = default;     // Copy assignment
  Container &operator=(Container &&) noexcept = default; // Move assignment
};

class Vector_container : public Container {
public:
  explicit Vector_container(std::size_t s) : v(s) {}
  Vector_container(const Vector_container &other) = default;
  Vector_container(Vector_container &&) noexcept = default;
  ~Vector_container() override = default;

  Vector_container &operator=(const Vector_container &) = default;
  Vector_container &operator=(Vector_container &&) noexcept = default;

  const double &operator[](std::size_t i) const override { return v[i]; }
  [[nodiscard]] std::size_t size() const override { return v.size(); }

private:
  Vector v;
};

class List_container : public Container {
public:
  List_container() = default;
  List_container(std::initializer_list<double> il) : ld{il} {};
  List_container(const List_container &) = default;
  List_container(List_container &&) noexcept = default;
  ~List_container() override = default;

  List_container &operator=(const List_container &) = default;
  List_container &operator=(List_container &&) noexcept = default;

  const double &operator[](std::size_t i) const override;
  [[nodiscard]] std::size_t size() const override { return ld.size(); }

private:
  std::list<double> ld;
};