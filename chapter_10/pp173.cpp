#include <iostream>
#include <sstream>
#include <stdexcept>

void test() {
  std::ostringstream oss;

  oss << "{temperature," << std::scientific << 123.4567890 << "}";
  std::cout << oss.str() << '\n';
}

////////////////////////////////////////////////////////////////////////////////

template <typename Target = std::string, typename Source = std::string>
Target to(Source arg)  // Convert Source to Target
{
  std::stringstream interpreter;
  Target result;

  if (!(interpreter << arg)                  // Write arg into stream
      || !(interpreter >> result)            // Read result from stream
      || !(interpreter >> std::ws).eof()) {  // Stuff left in stream?
    throw std::runtime_error{"to<>() failed"};
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  test();

  try {
    // Very explicit (and verbose)
    auto x1{to<std::string, double>(1.2)};
    // Source is deduced to double
    auto x2{to<std::string>(1.2)};
    // Target is defaulted to std::string; Source is deduced to double
    auto x3{to<>(1.2)};
    // Target is defaulted to std::string; Source is deduced to double
    auto x4{to(1.2)};

    // Avoid significant overhead
    std::ios_base::sync_with_stdio(false);

    std::cout << x1 << '\n';
    std::cout << x2 << '\n';
    std::cout << x3 << '\n';
    std::cout << x4 << '\n';
  } catch (std::exception& err) {
    std::cerr << "  what(): " << err.what() << '\n';
  }
}
