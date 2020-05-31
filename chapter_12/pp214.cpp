#include <algorithm>
#include <chrono>
#include <cppitertools/itertools.hpp>
#include <execution>
#include <iostream>
#include <random>
#include <vector>

const int vector_size = 100'000'000;

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(1, vector_size);

  std::vector<double> original_v;
  original_v.reserve(vector_size);

  for ([[maybe_unused]] auto i : iter::range(vector_size)) {
    original_v.push_back(dis(gen));
  }

  std::vector<double> v;
  v.reserve(vector_size);

  using namespace std::chrono;

  // Sequential (same as the default)
  v.clear();
  std::cout << "seq: " << std::flush;
  std::copy(original_v.begin(), original_v.end(), std::back_inserter(v));
  auto start = steady_clock::now();
  std::sort(std::execution::seq, v.begin(), v.end());
  auto end = steady_clock::now();
  std::cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

  // May be parallelized
  std::cout << "par: " << std::flush;
  v.clear();
  std::copy(original_v.begin(), original_v.end(), std::back_inserter(v));
  start = steady_clock::now();
  std::sort(std::execution::par, v.begin(), v.end());
  end = steady_clock::now();
  std::cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

  // May be parallelized and/or vectorized
  std::cout << "par_unseq: " << std::flush;
  v.clear();
  std::copy(original_v.begin(), original_v.end(), std::back_inserter(v));
  start = steady_clock::now();
  std::sort(std::execution::par_unseq, v.begin(), v.end());
  end = steady_clock::now();
  std::cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

  // May be vectorized (does not work in MSVC)
  // std::cout << "unseq: " << std::flush;
  // v.clear();
  // std::copy(original_v.begin(), original_v.end(), std::back_inserter(v));
  // start = steady_clock::now();
  // std::sort(std::execution::unseq, v.begin(), v.end());
  // end = steady_clock::now();
  // std::cout << duration_cast<milliseconds>(end - start).count() << " ms\n";

  // std::cout << "\n";
  // for (const auto& x : v) {
  //   std::cout << x << ' ';
  // }
  // std::cout << '\n';
}