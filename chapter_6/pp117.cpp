#include <iostream>
#include <list>
#include <string>

#include "vector.hpp"

using namespace std::string_literals;

////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Less_than {
  const T val;  // Value to compare against
 public:
  // See
  // https://stackoverflow.com/questions/51705967/advantages-of-pass-by-value-and-stdmove-over-pass-by-reference
  explicit Less_than(T v) : val{std::move(v)} {}
  // explicit Less_than(const T& v) : val{v} {}
  // explicit Less_than(T&& v) : val{std::move(v)} {}
  bool operator()(const T& x) const { return x < val; }  // Call operator
};

std::tuple<bool, bool, bool> fct(int n, const std::string& s) {
  // lti(i) will compare i to 42 using < (i<42)
  int x = 42;
  Less_than lti{x};
  x = 1;
  // lts(s) will compare s to "Backus" using < (s<"Backus")
  Less_than lts{"Backus"s};
  // "Naur" is a C-style string, so we nedd <string> to get the right <
  Less_than<std::string> lts2{"Naur"};

  bool b1 = lti(n);   // true if n<42
  bool b2 = lts(s);   // true if s<"Backus"
  bool b3 = lts2(s);  // true if s<"Naur"
  return {b1, b2, b3};
}

////////////////////////////////////////////////////////////////////////////////

template <typename C, typename P>  // std::SequenceContainer, Callable P
int count(const C& c, P pred) {
  int cnt = 0;
  for (const auto& x : c) {
    if (pred(x)) {
      ++cnt;
    }
  }
  return cnt;
}

void f(const Vector<int>& vec, const std::list<std::string>& lst, int x,
       const std::string& s) {
  std::cout << "\nUsing Less_than:\n";
  std::cout << "Number of values less than " << x << ": "
            << count(vec, Less_than{x}) << '\n';
  std::cout << "Number of values less than " << s << ": "
            << count(lst, Less_than{s}) << '\n';

  std::cout << "\nUsing lambda expressions:\n";
  std::cout << "Number of values less than " << x << ": "
            << count(vec, [&](int a) { return a < x; }) << '\n';
  std::cout << "Number of values less than " << s << ": "
            << count(lst, [&](const std::string& a) { return a < s; }) << '\n';
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  auto [b1, b2, b3] = fct(10, "C++");
  std::cout << b1 << ' ' << b2 << ' ' << b3 << '\n';

  Vector vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list lst{"a"s, "b"s, "c"s, "x"s};
  f(vec, lst, 5, "c"s);
}
