#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

void use() {
  std::ifstream in("file.txt");  // Input file
  if (!in) {
    std::cerr << "No file\n";
  }

  // U.S. postal code pattern
  // \w{2} = two letters
  // \s* = zero or more spaces
  // \d{5} = five digits
  // (-\d{4})?) = optionally, a dash followed by four digits
  std::regex pat{R"(\w{2}\s*\d{5}(-\d{4})?)"};

  int lineno = 0;

  for (std::string line; getline(in, line);) {
    ++lineno;
    // Matched strings go here
    std::smatch matches;
    // Search for pat in line
    while (std::regex_search(line, matches, pat)) {
      // if (std::regex_search(line, matches, pat)) {
      // The complete match
      std::cout << lineno << ": " << matches[0] << '\n';
      // If there is a sub-pattern and if it is matched
      if (1 < matches.size() && matches[1].matched) {
        // Submatch (the optional four-digit subpattern)
        std::cout << "\t: " << matches[1] << "\n";
      }
      line = matches.suffix();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

bool is_identifier(std::string_view s) {
  // Underscore or letter followed by zero or more underscores,
  // letters, or digits
  std::regex pat{R"([_[:alpha:]]\w*)"};

  std::match_results<std::string_view::const_iterator> m;
  return std::regex_match(s.begin(), s.end(), m, pat);
  // return std::regex_match(s, pat); // If s is a std::string
}

////////////////////////////////////////////////////////////////////////////////

void test() {
  std::string input = "aa as; asd ++e^asdf asdfg";
  std::regex pat{R"(\s+(\w+))"};
  for (std::sregex_iterator p(input.begin(), input.end(), pat);
       p != std::sregex_iterator{}; ++p) {
    std::cout << (*p)[1] << '\n';
  }
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  using namespace std::string_view_literals;

  use();

  auto x = "_0abc12_3"sv;
  if (is_identifier(x)) {
    std::cout << x << " is an identifier\n";
  }

  test();
}