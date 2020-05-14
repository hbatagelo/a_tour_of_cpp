#include <array>
#include <iostream>

// Count the number of occurrences of x in p[]
// p is assumed to point to a zero-terminated array of char (or nothing).
//
// The characters in a string literal are immutable, so to handle
// count_x_original("Hello!"), count_x_original() was a declared with a char*
// argument.
//
// This version uses std::string_view and range-based for to avoid pointer
// arithmetic.
int count_x(const char *p, char x) {
  if (p == nullptr) {
    return 0;
  }
  auto count{0};
  for (const auto &c : std::string_view(p)) {
    if (c == x) {
      ++count;
    }
  }
  return count;
}

int main() { std::cout << count_x("A Tour of C++", 'o') << '\n'; }