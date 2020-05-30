#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

struct Entry {
  std::string name{};
  int number{};

  // auto operator<=>(const Entry&) const noexcept = default;
};

bool operator<(const Entry& lhs, const Entry& rhs) {
  return (lhs.name == rhs.name) ? (lhs.number < rhs.number)
                                : (lhs.name < rhs.name);
}

bool operator==(const Entry& lhs, const Entry& rhs) {
  return lhs.name == rhs.name && lhs.number == rhs.number;
}

std::ostream& operator<<(std::ostream& os, const Entry& e) {
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

void f(std::vector<Entry>& vec, std::list<Entry>& lst) {
  // Use < for order
  std::sort(vec.begin(), vec.end());
  // Don't copy adjacent equal elements
  std::unique_copy(vec.begin(), vec.end(), lst.begin());
}

std::list<Entry> f(std::vector<Entry>& vec) {
  std::list<Entry> res;
  std::sort(vec.begin(), vec.end());
  std::unique_copy(vec.begin(), vec.end(), std::back_inserter(res));
  return res;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  std::vector<Entry> vec{{"David Hume", 123456},
                         {"Karl Popper", 234567},
                         {"Bertrand Arthur William Russell", 345678}};

  std::list<Entry> lst1(vec.size());
  f(vec, lst1);
  for (const auto& x : lst1) {
    std::cout << x.name << ' ' << x.number << '\n';
  }

  std::cout << '\n';

  std::list<Entry> lst2{f(vec)};
  for (const auto& x : lst1) {
    std::cout << x.name << ' ' << x.number << '\n';
  }
}