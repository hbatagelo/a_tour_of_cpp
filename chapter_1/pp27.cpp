#include <array>
#include <iostream>

const int n = 10;

void copy_fct() {
  std::array<int, n> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::array<int, n> v2{}; // To become a copy of v1

  for (ulong i = 0; i != n; ++i) { // Copy elements
    v2.at(i) = v1.at(i);
  }
}

void print() {
  std::array<int, n> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto x : v) { // For	each	x	in	v
    std::cout << x << '\n';
  }
  for (auto x : {10, 21, 32, 43, 54, 65}) {
    std::cout << x << '\n';
  }
}

int main() {
  copy_fct();
  print();
}