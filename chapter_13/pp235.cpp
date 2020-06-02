#include <any>
#include <iostream>
#include <istream>
#include <string>

std::any compose_message(std::istream& s) {
  std::string mess;

  bool no_problems{true};
  for (std::string str; s >> str;) {
    if (str == "x") no_problems = false;
    mess += str;
  }

  if (no_problems) return mess;  // Return a string

  return 0;  // Return an int
}

////////////////////////////////////////////////////////////////////////////////

// echo a b c | ./build/bin/pp235       -> abc
// echo a x c | ./build/bin/pp235       -> problem: 0

int main() {
  std::ios_base::sync_with_stdio(false);

  auto m{compose_message(std::cin)};
  if (m.type() == typeid(std::string)) {
    auto s = std::any_cast<std::string>(m);
    std::cout << s << '\n';
  } else
    std::cerr << "problem: " << std::any_cast<int>(m) << '\n';
}