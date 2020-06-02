#include <forward_list>
#include <iostream>
#include <iterator>
#include <vector>

template <typename Ran>  // For random-access iterators
void sort_helper(Ran beg, Ran end, std::random_access_iterator_tag) {
  std::sort(beg, end);
}

// template <typename C>
// using Value_type = typename C::value_type;

template <typename For>  // For forward iterators
void sort_helper(For beg, For end, std::forward_iterator_tag) {
  // std::vector<typename For::value_type> v{beg, end};
  // std::vector<Value_type<For>> v{beg, end};
  std::vector<std::iter_value_t<For>> v{beg, end};

  std::sort(v.begin(), v.end());
  std::copy(v.begin(), v.end(), beg);
}

// template <typename C>
// using Iterator_type = typename C::iterator;  // C's iterator type

// template <typename Iter>
// using Iterator_category =
//     typename std::iterator_traits<Iter>::iterator_category;  // Iter's
//     category

template <typename C>
void sort(C& c) {
  // using Iter = Iterator_type<C>;
  // sort_helper(c.begin(), c.end(), Iterator_category<Iter>{});
  sort_helper(
      c.begin(), c.end(),
      typename std::iterator_traits<typename C::iterator>::iterator_category{});
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