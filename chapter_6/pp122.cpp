#include <iostream>
#include <map>
#include <vector>

template <typename T>
struct space_vector {
  float x, y, z;
};

////////////////////////////////////////////////////////////////////////////////
// Variable templates

template <typename T>
constexpr T viscosity = 0.4;

template <typename T>
constexpr space_vector<T> external_acceleration = {T{}, T{static_cast<T>(-9.8)},
                                                   T{}};

template <typename T, typename T2>
constexpr bool Assignable = std::is_assignable<T&, T2>::value;

template <typename T>
void testing() {
  static_assert(Assignable<T&, double>, "can't assign a double");
  static_assert(Assignable<T&, std::string>, "can't assign a string");
}

////////////////////////////////////////////////////////////////////////////////
// Alias templates
template <typename C>
using Value_type = typename C::value_type;  // the type of C's elements

template <typename Container>
void algo([[maybe_unused]] Container& c) {
  std::vector<Value_type<Container>> vec;  // Keep results here
}

template <typename Value>
using String_map = std::map<std::string, Value>;
String_map<int> m;  // m is a std::map<std::string, int>

////////////////////////////////////////////////////////////////////////////////
// Compile-time if
template <typename T>
void update([[maybe_unused]] T& target) {
  if constexpr (std::is_pod_v<T>) {
    std::cout << "Call simple_and_fast(target)\n";
  } else {
    std::cout << "Call slow_and_safe(target)\n";
  }
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  // Variable templates example usage
  auto vis2 = 2 * viscosity<double>;
  auto acc = external_acceleration<float>;
  std::cout << "vis2: " << vis2 << '\n';
  std::cout << "acc: " << acc.x << ' ' << acc.y << ' ' << acc.z << ' ' << '\n';

  // testing<int>();
  testing<std::string>();
}