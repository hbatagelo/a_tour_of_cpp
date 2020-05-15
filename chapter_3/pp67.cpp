#include <complex>
#include <iostream>
#include <map>
#include <string>

struct Entry {
  std::string name;
  int value;
};

// naive function (for a better version, see §10.5)
Entry read_entry(std::istream &is) {
  std::string s;
  int i{};
  is >> s >> i;
  return {s, i};
}

// Increment the value of each element of m
void incr(std::map<std::string, int> &m) {
  for (auto &[key, value] : m) {
    ++value;
  }
}

int main() {
  auto e = read_entry(std::cin);
  std::cout << "{" << e.name << "," << e.value << "}\n";

  // Structured binding
  auto [n, v]{read_entry(std::cin)};
  std::cout << "{" << n << "," << v << "}\n";

  std::cout << "\n";

  // Structured binding with map
  std::map<std::string, int> m;
  m.insert({"a", 1});
  m["b"] = 2;
  incr(m);
  for (const auto &[key, value] : m) {
    std::cout << "{" << key << "," << value << "}\n";
  }
}