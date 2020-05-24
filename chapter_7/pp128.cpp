#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

template <typename T>
concept Addable = requires(T a, T b) {
  a + b;
};

template <typename T>
requires Addable<T> auto add(T a, T b) {
  return a + b;
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
concept Sequence = std::is_convertible_v<
    typename std::iterator_traits<typename T::iterator>::iterator_category,
    std::input_iterator_tag>;

template <typename T>
concept Number = std::is_integral_v<T>;

template <typename T, typename T2>
concept Arithmetic = std::is_arithmetic_v<T>&& std::is_arithmetic_v<T2>;

// template <Sequence Seq, Number Num>
//  requires Arithmetic<typename Seq::value_type, Num>
// template <Sequence Seq, Number Num>
//  requires Sequence<Seq> && Number<Num> && Arithmetic<typename
//  Seq::value_type, Num>
template <Sequence Seq, Arithmetic<typename Seq::value_type> Num>
Num sum(Seq s, Num v) {
  for (const auto& x : s) {
    v += x;
  }
  return v;
}

////////////////////////////////////////////////////////////////////////////////

template <typename I>
concept Random_access_iterator =
    std::is_same_v<typename std::iterator_traits<I>::iterator_category,
                   std::random_access_iterator_tag>;

template <typename Iter>
requires(!Random_access_iterator<Iter>) void advance(
    Iter p,
    int n)  // Move p n elements forward
{
  std::cout << "Using slow iterator\n";
  while (n--) {
    ++p;  // A forward iterator has ++, but not + or +=
  }
}

// template <Random_access_iterator Iter>
template <typename Iter>
requires requires(Iter p, int i) {
  p[i];
  p + i;
}
void advance(Iter p, int n)  // Move p n elements forward
{
  std::cout << "Using fast iterator\n";
  p + n;  // A random access iterator has +=
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  // struct A {};
  // A a{};
  int a{};
  add(a, a);

  // std::cout << sum(0, 10) << '\n';
  std::vector<int> v{1, 2, 3, 4, 5};
  std::list<int> l{1, 2, 3, 4, 5};

  std::cout << sum(v, 10) << '\n';

  advance(std::begin(v), 3);  // Use random_access_iterator
  advance(l.begin(), 3);      // Use forward_iterator
}