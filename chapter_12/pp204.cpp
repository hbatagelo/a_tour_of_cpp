#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

void f() {
  // Write string to cout
  std::ostream_iterator<std::string> oo{std::cout};

  *oo = "Hello, ";  // Meaning cout<<"Hello, "
  ++oo;
  *oo = "world!\n";  // Meaning cout<<"world!\n"
}

////////////////////////////////////////////////////////////////////////////////

bool use1(const std::string& from, const std::string& to) {
  std::ifstream is{from};                     // Input stream for file "from"
  std::istream_iterator<std::string> ii{is};  // Input iterator for stream
  std::istream_iterator<std::string> eos{};   // Input sentinel

  std::ofstream os{to};  // Output stream for file "to"
  // Output iterator for stream (\n is the delimiter)
  std::ostream_iterator<std::string> oo{os, "\n"};

  std::vector<std::string> b{ii, eos};  // b is a vector initialized from input

  std::sort(b.begin(), b.end());  // Sort the buffer
  // Copy buffer to output, discard replicated values
  std::unique_copy(b.begin(), b.end(), oo);

  return !is.eof() || !os;  // Return error state
}

bool use2(const std::string& from, const std::string& to) {
  std::ifstream is{from};  // Input stream for file "from"
  std::ofstream os{to};    // Output stream for file "to"

  // Read input
  std::set<std::string> b{std::istream_iterator<std::string>{is},
                          std::istream_iterator<std::string>{}};

  // Copy to output
  std::copy(b.begin(), b.end(), std::ostream_iterator<std::string>{os, "\n"});

  return !is.eof() || !os;  // Return error state
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  f();

  std::string from;
  std::string to;
  std::cout << "Enter source file name: ";
  std::cin >> from;
  std::cout << "Enter target file name: ";
  std::cin >> to;

  // return static_cast<int>(use1(from, to));
  return static_cast<int>(use2(from, to));
}