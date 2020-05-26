#include <ios>
#include <iostream>
#include <vector>

struct Entry {
  std::string name;
  int number{};
};

std::ostream& operator<<(std::ostream& os, const Entry& e) {
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

// Read { "name", number } pair.
// Note: formatted with { " ", and }
std::istream& operator>>(std::istream& is, Entry& e) {
  // Start with a {"
  if (char c{}, c2{}; is >> c && c == '{' && is >> c2 && c2 == '"') {
    std::string name;  // The default value of a string is the empty string: ""

    // istream::get doesn't skip whitespaces
    while (is.get(c) && c != '"') {  // Anything before a " is part of the name
      name += c;
    }

    if (is >> c && c == ',') {  // Read the number and a }
      if (int number{}; is >> number >> c && c == '}') {
        e = {name, number};  // Assign to the entry
        return is;
      }
    }
  }
  is.setstate(std::ios_base::failbit);  // Register the failure in the stream
  return is;
}

////////////////////////////////////////////////////////////////////////////////

// echo	{ \"J Cleese\", 1234   } {\"Michael Palin\", 987654} | ./build/bin/pp169

int main() {
  // Corresponding regular expression: {\s*".*"\s*,\s*\d+\s*}
  for (Entry ee; std::cin >> ee;) {  // Read from std::cin into ee
    std::cout << ee << '\n';         // Write ee to std::cout
  }
}
