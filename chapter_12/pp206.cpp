#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>

struct GreaterThan {
  explicit GreaterThan(int v) : val{v} {}
  bool operator()(const std::pair<std::string, int>& r) const {
    return r.second > val;
  }

 private:
  int val{};
};

void f(std::map<std::string, int>& m) {
  // p is a std::map<std::string, int>::iterator
  // auto p = std::find_if(m.begin(), m.end(), Greater_than{42});
  auto p = std::find_if(
      m.begin(), m.end(),
      [](const std::pair<std::string, int>& r) { return r.second > 42; });

  if (p != m.end()) {
    std::cout << (*p).first << ' ' << p->second << '\n';
  }
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  using namespace std::string_literals;

  std::map<std::string, int> p{{"abc"s, 12}, {"def"s, 43}};
  f(p);
}