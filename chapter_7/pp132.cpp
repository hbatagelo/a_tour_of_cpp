#include <ranges>
#include <vector>

template <typename T>
concept Equality_comparable = requires(T a, T b) {
  { a == b }
  ->std::__detail::__boolean_testable;  // Compare Ts with ==
  { a != b }
  ->std::__detail::__boolean_testable;  // Compare Ts with !=
};

// Succeeds
static_assert(Equality_comparable<int>);

struct S {
  int a{};
};
// Fails because structs don't automatically get == and !=
// static_assert(Equality_comparable<S>);

template <typename T, typename T2 = T>
concept Equality_comparable2 = requires(T a, T b) {
  { a == b }
  ->std::__detail::__boolean_testable;
  { a != b }
  ->std::__detail::__boolean_testable;
  { b == a }
  ->std::__detail::__boolean_testable;
  { b != a }
  ->std::__detail::__boolean_testable;
};

static_assert(Equality_comparable2<int, double>);  // Succeeds
static_assert(Equality_comparable2<int>);  // Succeeds (T2 is defaulted to int)
// static_assert(Equality_comparable2<S, std::string>); // Fails

////////////////////////////////////////////////////////////////////////////////

template <typename T>
using Value_type = typename T::value_type;

template <typename T>
using Iterator_type = std::ranges::iterator_t<T>;

template <typename I>
concept Input_iterator = requires(I a, I b) {
  a == b;
  a != b;
  *a;
  ++a;
  a++;
  *a++;
};

// std::is_base_of_v<std::input_iterator_tag, I>;

template <typename S>
concept Sequence = requires(S a) {
  typename Value_type<S>;     // S must have a value
  typename Iterator_type<S>;  // S must have an iterator type
  { std::begin(a) }
  ->std::same_as<Iterator_type<S>>;  // begin(s) must return an iterator
  { std::end(a) }
  ->std::same_as<Iterator_type<S>>;  // end(s) must return an iterator

  requires std::same_as<Value_type<S>, Value_type<Iterator_type<S>>>;
  requires Input_iterator<Iterator_type<S>>;
};

static_assert(Sequence<std::vector<int>>);
// static_assert(Sequence<int>); // Fails

////////////////////////////////////////////////////////////////////////////////

int main() {}