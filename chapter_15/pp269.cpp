#include <future>
#include <iostream>
#include <numeric>
#include <vector>

// Compute the sum of [beg:end) starting with the initial value init
double accum(double* beg, double* end, double init) {
  return std::accumulate(beg, end, init);
}

// Spawn many tasks if v is large enough
double comp(std::vector<double>& v) {
  auto* v_begin{v.data()};
  auto* v_end{std::next(v.data(), static_cast<long>(v.size()))};

  // Is it worth using concurrency?
  if (v.size() < 10000) return accum(v_begin, v_end, 0.0);

  auto* v_1q{std::next(v.data(), v.size() / 4)};
  auto* v_2q{std::next(v.data(), v.size() / 2)};
  auto* v_3q{std::next(v.data(), v.size() * 3 / 4)};

  // Producers
  auto f0{std::async(accum, v_begin, v_1q, 0.0)};  // 1st quarter
  auto f1{std::async(accum, v_1q, v_2q, 0.0)};     // 2nd quarter
  auto f2{std::async(accum, v_2q, v_3q, 0.0)};     // 3rd quarter
  auto f3{std::async(accum, v_3q, v_end, 0.0)};    // 4th quarter

  // Consumers

  // Collect and combine the results (caller thread)
  // return f0.get() + f1.get() + f2.get() + f3.get();

  // Collect and combine the results (separate consumer thread)
  double res{};
  auto consumer =
      std::thread{[&]() { res = f0.get() + f1.get() + f2.get() + f3.get(); }};
  consumer.join();

  return res;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  std::vector<double> v(100'000);
  std::iota(v.begin(), v.end(), 1);
  std::cout << comp(v) << '\n';
}