#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std::string_literals;

template <typename T, typename... Tail>
void print(T head, Tail... tail) {
  // What we do for each argument, e.g.,
  std::cout << head;
  if constexpr (sizeof...(tail) > 0) {
    std::cout << ' ';
    print(tail...);
  }
}

void user() {
  print("first:", 1, 2.2, "hello\n"s);
  print("second:", 0.2, 'c', "yuck!"s, 0, 1, 2, '\n');
}

////////////////////////////////////////////////////////////////////////////////

// template <typename T>
// concept Number = (std::integral<T> || std::floating_point<T>);
// template <Number... T>
template <typename... T>
int sum(T... v) {
  // Right fold
  // (v[0]+(v[1]+(v[2]+(v[3]+(v[4]+0)))))
  return (static_cast<int>(v) + ... + 0);
}

// template <Number... T>
template <typename... T>
int sum2(T... v) {
  // Left fold
  // (((((0+v[0])+v[1])+v[2])+v[3])+v[4]).
  return (0 + ... + static_cast<int>(v));
}

////////////////////////////////////////////////////////////////////////////////

template <typename... T>
void print2(T&&... args) {
  // Left fold
  (std::cout << ... << args) << '\n';
}

////////////////////////////////////////////////////////////////////////////////

template <typename Res, typename... Ts>
std::vector<Res> to_vector(Ts&&... ts) {
  std::vector<Res> res;
  (res.push_back(ts), ...);  // No initial value needed
  return res;
}

template <typename... Ts>
int fct(Ts&&... ts) {
  // args[i] is the ith argument
  auto args = to_vector<std::string>(ts...);
  for (auto& x : args) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
  return 0;
}

int main() {
  user();

  auto x{sum(1, 2, 3, 4, 5)};
  std::cout << x << '\n';
  std::cout << sum('a', 2.4, x) << '\n';

  // (((((std::cout << "Hello!"s) << ' ') << "World ") << 2017) << '\n');
  print2("hello!"s, ' ', "World "s, 2017);

  auto y = to_vector<double>(1, 2, 4.5, 'a');
  std::cout << y.size() << '\n';
  int z = fct("foo"s, "bar"s);
  std::cout << z << '\n';
}