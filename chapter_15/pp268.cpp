#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

// Compute the sum of [beg:end) starting with the initial value init
double accum(double* beg, double* end, double init) {
  return std::accumulate(beg, end, init);
}

double comp(std::vector<double>& v) {
  // Type of task
  using Task_type = double(double*, double*, double);

  // Package the task (i.e., accum)
  std::packaged_task<Task_type> pt0{accum};
  std::packaged_task<Task_type> pt1{accum};

  // Get hold of pt0's and pt1's future
  std::future<double> f0{pt0.get_future()};
  std::future<double> f1{pt1.get_future()};

  // Start a thread for pt0 and pt1
  // With pointer arithmetic
  //  double* first{&v[0]};
  //  std::thread t1{std::move(pt0), first, first + v.size() / 2, 0};
  //  std::thread t2{std::move(pt1), first + v.size() / 2, first + v.size(), 0};

  // Start a thread for pt0 and pt1 (producers)
  // Without pointer arithmetic
  auto* v_begin{v.data()};
  auto* v_half{std::next(v.data(), v.size() / 2)};
  auto* v_end{std::next(v.data(), static_cast<long>(v.size()))};
  std::thread t1{std::move(pt0), v_begin, v_half, 0};
  std::thread t2{std::move(pt1), v_half, v_end, 0};

  // Get the results (consumer)
  double res{f0.get() + f1.get()};

  t1.join();
  t2.join();

  return res;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  std::vector<double> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::cout << comp(v) << '\n';
}