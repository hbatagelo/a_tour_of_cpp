#include <cppitertools/itertools.hpp>
#include <gsl/string_span>
#include <iostream>
#include <string>
#include <string_view>

std::string compose(const std::string& name, const std::string& domain) {
  return name + '@' + domain;
}

void m2(std::string& s1, std::string& s2) {
  s1 = s1 + '\n';  // Append newline
  s2 += '\n';      // Append newline
}

void m3() {
  std::string name{"Niels Stroustrup"};

  std::string s{name.substr(6, 10)};  // s = "Stroustrup"
  name.replace(0, 5, "nicholas");     // name becomes "nicholas Stroustrup"
  name[0] = static_cast<char>(
      toupper(name[0]));  // name becomes "Nicholas Stroustrup"

  std::cout << name << '\n';
}

////////////////////////////////////////////////////////////////////////////////

std::string cat(std::string_view sv1, std::string_view sv2) {
  std::string res(sv1.length() + sv2.length(), ' ');

  //////////////////////////////////////////////////////////////////////////////
  // ulong i = 0;
  // for (auto sp = gsl::string_span<>(res); auto c : sv1) {
  //   sp[i++] = c;
  // }
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Using cppitertools
  for (auto sp = gsl::string_span<>(res);
       auto&& [i, e] : iter::enumerate(sv1)) {
    sp[i] = e;
  }
  //////////////////////////////////////////////////////////////////////////////
  std::copy(sv2.begin(), sv2.end(), &res[sv1.length()]);

  return res;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  using namespace std::string_view_literals;

  auto addr{compose("dmr", "bell-labs.com")};
  std::cout << addr << '\n';

  m3();

  std::string king = "Harold";
  auto s1 = cat(king, "William");               // string and const char*
  auto s2 = cat(king, king);                    // string and string
  auto s3 = cat("Edward", "Stephen"sv);         // const char* and string_view
  auto s4 = cat("Canute"sv, king);              // string_view and string
  auto s5 = cat({&king[0], 2}, "Henry"sv);      // HaHenry
  auto s6 = cat({&king[0], 2}, {&king[2], 4});  // Harold
  for (const auto& s : {s1, s2, s3, s4, s5, s6}) {
    std::cout << s << '\n';
  }
}