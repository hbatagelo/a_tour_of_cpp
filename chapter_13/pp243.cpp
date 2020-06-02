#include <forward_list>
#include <iostream>
#include <ranges>
#include <type_traits>
#include <typeinfo>
#include <vector>

// Use for std::vector and other types
template <std::random_access_iterator Iter>
void sort(Iter p, Iter q) {
  std::sort(p, q);
}

// Use for std::list and other types supporting just forward traversal
template <std::forward_iterator Iter>
void sort(Iter p, Iter q) {
  std::vector<std::iter_value_t<Iter>> v{p, q};
  std::sort(v.begin(), v.end());
  std::copy(v.begin(), v.end(), p);
}

// Use the appropriate sort
template <std::ranges::range R>
void sort(R& r) {
  sort(r.begin(), r.end());
}

void test(std::vector<std::string>& v, std::forward_list<int>& lst) {
  sort(v);    // Sort the vector
  sort(lst);  // Sort the singly-linked list
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  using namespace std::string_literals;
  std::vector v{"x"s, "g"s, "e"s, "a"s};
  std::forward_list l{90, 60, 42, 2, 40, 10};

  test(v, l);

  for (const auto& x : v) std::cout << x << ' ';
  std::cout << '\n';
  for (const auto& x : l) std::cout << x << ' ';
  std::cout << '\n';
}