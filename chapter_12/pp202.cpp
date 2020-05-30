#include <iostream>
#include <list>
#include <string>
#include <vector>

template <typename T>
using Iterator = typename T::iterator;  // T's iterator

// Fill all occurrences of v in c
template <typename C, typename V>
std::vector<Iterator<C>> find_all(C& c, const V& v) {
  std::vector<Iterator<C>> res;
  for (auto p = c.begin(); p != c.end(); ++p) {
    if (*p == v) {
      res.push_back(p);
    }
  }
  return res;
}

////////////////////////////////////////////////////////////////////////////////

using namespace std::string_literals;

int main() {
  std::string m{"Mary had a little lamb"s};

  for (const auto& p : find_all(m, 'a')) {  // p is a string::iterator
    if (*p != 'a') {
      std::cerr << "string bug!\n";
    }
  }

  std::list<double> ld{1.1, 2.2, 3.3, 1.1};
  for (const auto& p : find_all(ld, 1.1)) {  // p is a list<double>::iterator
    if (*p != 1.1) {
      std::cerr << "list bug!\n";
    }
  }

  std::vector<std::string> vs{"red"s,   "blue"s,   "green"s,
                              "green"s, "orange"s, "green"s};
  for (const auto& p :
       find_all(vs, "red"s)) {  // p is a vector<string>::iterator
    if (*p != "red") {
      std::cerr << "vector bug!\n";
    }
  }

  for (auto& p : find_all(vs, "green"s)) {
    *p = "vert"s;
  }

  for (const auto& p : vs) {
    std::cout << p << '\n';
  }
}