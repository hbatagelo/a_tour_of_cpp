#include <array>

const int n = 10;

void increment() {
  std::array<int, n> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (auto &x : v) {  // Add 1 to each x in v
    ++x;
  }
}

int main() { increment(); }