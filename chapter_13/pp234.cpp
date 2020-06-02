#include <iostream>
#include <istream>
#include <optional>
#include <string>

std::optional<std::string> compose_message(std::istream& s) {
  std::string mess;

  bool no_problems{true};
  for (std::string str; s >> str;) {
    if (str == "x") no_problems = false;
    mess += str;
  }

  if (no_problems) return mess;
  return {};  // The empty optional
}

////////////////////////////////////////////////////////////////////////////////

int cat(std::optional<int> a, std::optional<int> b) {
  int res{};
  if (a) res += *a;
  if (b) res += *b;
  return res;
}

////////////////////////////////////////////////////////////////////////////////

// echo a b c | ./build/bin/pp234       -> abc
// echo a x c | ./build/bin/pp234       -> problem

int main() {
  std::ios_base::sync_with_stdio(false);

  if (auto m{compose_message(std::cin)})
    std::cout << *m << '\n';  // Note the dereference (*)
  else
    std::cerr << "problem\n";

  [[maybe_unused]] int x = cat(17, 19);
  [[maybe_unused]] int y = cat(17, {});
  [[maybe_unused]] int z = cat({}, {});
}