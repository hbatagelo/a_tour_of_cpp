#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

struct Record {
  std::string name;
  int number{};
};

// Compare names
auto less = [](const Record& r1, const Record& r2) {
  return r1.name < r2.name;
};

std::ostream& operator<<(std::ostream& stream, const Record& r) {
  return stream << r.name;
}

// Assume that v is sorted on its "name" field
void f(const std::vector<Record>& v) {
  auto er = std::equal_range(v.begin(), v.end(), Record{"Reg"}, less);

  // Print all equal records
  for (auto p = er.first; p != er.second; ++p) {
    std::cout << *p << '\n';  // Assume that << is defined for Record
  }
}

// Using structured binding
// Assume that v is sorted on its "name" field
void f2(const std::vector<Record>& v) {
  auto [first, last] =
      std::equal_range(v.begin(), v.end(), Record{"Reg"}, less);

  // Print all equal records
  for (auto p = first; p != last; ++p) {
    std::cout << *p << '\n';  // Assume that << is defined for Record
  }
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  std::vector<Record> v{{"David Hume", 123456},
                        {"Reg", 42},
                        {"Karl Popper", 234567},
                        {"Bertrand Arthur William Russell", 345678}};

  std::sort(v.begin(), v.end(), less);

  f(v);
  f2(v);
}