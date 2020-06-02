#include <iostream>
#include <random>
#include <vector>

class RandInt {
 public:
  RandInt(int low, int high, ulong seed = 0) : re{seed}, dist{low, high} {}
  int operator()() { return dist(re); }
  void seed(ulong s) { re.seed(s); }

 private:
  std::default_random_engine re;
  std::uniform_int_distribution<> dist;
};

////////////////////////////////////////////////////////////////////////////////

int main() {
  constexpr int max{9};
  RandInt rnd{0, max};

  std::vector<std::size_t> histogram(max + 1);

  // Fill histogram with the frequencies of numbers [0:max]
  for (int i = 0; i != 200; ++i) {
    ++histogram[static_cast<std::size_t>(rnd())];
  }

  // Write out a bar graph
  for (std::size_t i = 0; i != histogram.size(); ++i) {
    std::cout << i << '\t';
    for (std::size_t j = 0; j != histogram[i]; ++j) {
      std::cout << '*';
    }
    std::cout << '\n';
  }
}