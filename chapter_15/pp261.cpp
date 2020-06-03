#include <algorithm>
#include <gsl/gsl>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

// Take input from v; place result in *res
void f(const std::vector<double>& v, gsl::not_null<double*> res) {
  *res = std::accumulate(v.begin(), v.end(), 0.0);
}

// Use return value
double g(const std::vector<double>& v) {
  return std::accumulate(v.begin(), v.end(), 0.0);
}

// Function object: do something with v
class F {
 public:
  explicit F(std::vector<double>& vv, gsl::not_null<double*> p)
      : v{vv}, res{p} {}
  void operator()() {
    std::transform(v.begin(), v.end(), v.begin(),
                   [n = 0](const auto& x) mutable { return x + n++; });
    *res = std::accumulate(v.begin(), v.end(), 0.0);
  }

 private:
  std::vector<double>& v;
  double* res;
};

////////////////////////////////////////////////////////////////////////////////

int main() {
  std::vector<double> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<double> vec2{10, 11, 12, 13, 14};
  std::vector<double> vec3{5, 4, 3, 2, 1, 0};

  double res1{};
  double res2{};
  double res3{};

  // Execute f(some_vec) and F(vec2) in separate threads
  std::thread t1{f, std::cref(vec1), &res1};  // f(vec1, &res1)
  std::thread t2{F{vec2, &res2}};             // F{vec2,&res2}()
  std::thread t3{[&]() { res3 = g(vec3); }};  // Capture locals by reference

  t1.join();
  t2.join();
  t3.join();

  // Show results
  std::cout << "res1, vec1: " << res1 << ", ";
  for (const auto& x : vec1) std::cout << x << ' ';
  std::cout << '\n';

  std::cout << "res2, vec2: " << res2 << ", ";
  for (const auto& x : vec2) std::cout << x << ' ';
  std::cout << '\n';

  std::cout << "res3, vec3: " << res3 << ", ";
  for (const auto& x : vec3) std::cout << x << ' ';
  std::cout << '\n';
}