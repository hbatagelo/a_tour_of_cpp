#include <iostream>
#include <string_view>
#include <vector>

std::vector<int> read_ints(std::istream& is, std::string_view terminator) {
  std::vector<int> res;
  for (int i{}; is >> i;) {
    res.push_back(i);
  }

  // Fine: end of file
  if (is.eof()) {
    std::cout << "EOF\n";
    return res;
  }

  // We failed to read an int; was it the terminator?
  if (is.fail()) {
    is.clear();  // Reset the state to good()
    is.unget();  // Put the non-digit back into the stream

    if (std::string s; std::cin >> s && s == terminator) {
      std::cout << "Failed (terminator found)\n";
      return res;
    }
    // Add fail() to cin's state
    std::cin.setstate(std::ios_base::failbit);
  }
  std::cout << "Failed (terminator not found)\n";
  return res;
}

////////////////////////////////////////////////////////////////////////////////

// echo 1 2 3 | ./build/bin/pp168       -> EOF
// echo 1 2 stop 3 | ./build/bin/pp168  -> Failed (terminator found)
// echo 1 2 sto 3 | ./build/bin/pp168   -> Failed (terminator not found)

int main() {
  using namespace std::string_view_literals;

  auto res{read_ints(std::cin, "stop"sv)};
  for (const auto& x : res) {
    std::cout << x << '\n';
  }
}