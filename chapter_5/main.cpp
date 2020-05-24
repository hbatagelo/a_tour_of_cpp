#include <complex>
#include <iostream>

#include "vector.hpp"

// The copy initialization is explicitly deleted when either:
// - a move initialization is user-declared, or
// - a move assignment operator is user-declared
class X {
 public:
  explicit X(int val);    // Ordinary initialization
  X();                    // Default initialization
  X(const X& other);      // Copy initialization
  X(X&& other) noexcept;  // Move initialization
  ~X() = default;         // Destructor

  X& operator=(const X& other);      // Copy assignment
  X& operator=(X&& other) noexcept;  // Move assignment

  void print() const { std::cout << value << '\n'; }

 private:
  int value{};
};

X::X() { std::cout << "Default initialization: " << value << '\n'; }

X::X(int val) : value{val} {
  std::cout << "Ordinary initialization: " << value << '\n';
}

X::X(const X& other) {
  std::cout << "Copy initialization " << value << " <- " << other.value << '\n';
  value = other.value;
}

X::X(X&& other) noexcept {
  std::cout << "Move initialization " << value << " <- " << other.value << '\n';
  value = other.value;
}

X& X::operator=(const X& other) {
  if (&other == this) {
    return *this;
  }

  std::cout << "Copy assigment: " << value << " <- " << other.value << '\n';
  value = other.value;

  return *this;
}

X& X::operator=(X&& other) noexcept {
  std::cout << "Move assigment: " << value << " <- " << other.value << '\n';
  value = other.value;

  return *this;
}

////////////////////////////////////////////////////////////////////////////////

Vector user() {
  Vector e(1000);
  Vector f(2000);
  Vector g(3000);

  g = e;             // Copy assignment
  f = std::move(e);  // Move assignment

  return g;
}

////////////////////////////////////////////////////////////////////////////////

// Imaginary literal
constexpr std::complex<double> operator""_i(long double arg) {
  return std::complex<double>{0, static_cast<double>(arg)};
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  X x{5};     // Ordinary initialization
  X y{10};    // Ordinary initialization
  X z;        // Default initialization
  X w{x};     // Copy initialization
  x = y;      // Copy assignment
  x = X{30};  // Move assignment
  X& a{x};    // Copy initialization not called
  a.print();
  // user(std::move(X{20})); // Move initialization

  std::complex<double> cp = 2.7182818 + 6.283185_i;
  std::cout << cp.real() << ", " << cp.imag() << '\n';

  std::cout << '\n';

  //////////////////////////////////////////////////////////////////////////////
  Vector b{10, 20, 30};
  Vector c{5, 6, 7};
  Vector d = b + c;  // Move constructor not called (copy elision)
  //////////////////////////////////////////////////////////////////////////////

  std::cout << '\n';

  //////////////////////////////////////////////////////////////////////////////
  Vector e = user();  // Move constructor not called (copy elision)
  //////////////////////////////////////////////////////////////////////////////

  std::cout << '\n';

  //////////////////////////////////////////////////////////////////////////////
  Vector f(1);
  f = user();  // Move assignment
  //////////////////////////////////////////////////////////////////////////////

  std::cout << '\n';
}