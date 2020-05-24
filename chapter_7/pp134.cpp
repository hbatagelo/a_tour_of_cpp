#include <iostream>
#include <list>
#include <vector>

// Non-generic
double sum(const std::vector<int>& v) {
  double res{};
  for (auto x : v) {
    res += x;
  }
  return res;
}

// Generic
template <typename Iter, typename Val>
Val accumulate(Iter first, Iter last, Val res) {
  for (auto p{first}; p != last; ++p) {
    res += *p;
  }
  return res;
}

// template <typename T, typename T2>
// concept Number = (std::integral<T> || std::floating_point<T>) &&
// std::same_as<T, T2> && requires(T a, T2 b) {b += a; };

// Using concepts
// A range is something with begin() and end()
template <std::ranges::range R, typename Val>
requires(std::integral<Val> || std::floating_point<Val>) Val
    accumulate(const R& r, Val res = 0) {
  for (auto p{std::begin(r)}; p != std::end(r); ++p) {
    res += static_cast<Val>(*p);
  }
  return res;
}

void use(const std::vector<int>& vec, const std::list<double>& lst) {
  auto sum{accumulate(std::begin(vec), std::end(vec), 0.0)};
  auto sum2{accumulate(std::begin(lst), std::end(lst), sum)};
  std::cout << sum << ' ' << sum2 << '\n';

  auto sum3{accumulate(vec, 0)};
  auto sum4{accumulate(lst, sum3)};
  std::cout << sum3 << ' ' << sum4 << '\n';
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  std::vector vec{1, 2, 3, 4, 5};
  std::list lst{1.0, 2.0, 3.0, 4.0, 5.0};
  use(vec, lst);
}