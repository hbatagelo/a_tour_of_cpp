#include <iostream>
#include <vector>

template <typename T> struct space_vector { float x, y, z; };

template <typename T> constexpr T viscosity = 0.4;

template <typename T>
constexpr space_vector<T> external_acceleration = {T{}, T{static_cast<T>(-9.8)},
                                                   T{}};

auto vis2 = 2 * viscosity<double>;
auto acc = external_acceleration<float>;

// Initializer alternatives
enum class Init_mode { zero, seq };

int main() {
  Init_mode m{Init_mode::seq};

  // Initialize a vector using a lambda expression
  std::vector<int> v = [&]() {
    switch (m) {
    case Init_mode::zero:
      return std::vector<int>{10};
    case Init_mode::seq:
      return std::vector<int>{42, 7};
    }
  }();

  std::cout << v.size() << '\n';
}