#include <iostream>
#include <string>
#include <unordered_set>

struct Record {
  std::string name;
  int product_code;
};

bool operator==(const Record& lhs, const Record& rhs) { return &lhs == &rhs; };

// A hash function for Record
struct RHash {
  std::size_t operator()(const Record& r) const {
    return std::hash<std::string>()(r.name) ^ std::hash<int>()(r.product_code);
  }
};

// Make a hash function for Record
namespace std {
template <>
struct hash<Record> {
  using argument_type = Record;
  using result_type = std::size_t;

  std::size_t operator()(const Record& r) const {
    return std::hash<std::string>()(r.name) ^ std::hash<int>()(r.product_code);
  }
};
}  // namespace std

// Set of Records using RecordHash for lookup
std::unordered_set<Record, RHash> my_set;
// std::unordered_set<Record> my_set;

////////////////////////////////////////////////////////////////////////////////

int main() {
  my_set.insert({"David Hume", 123456});
  my_set.insert({"Karl Popper", 234567});
  my_set.insert({"Bertrand Arthur William Russell", 345678});

  for (const auto& x : my_set) {
    std::cout << x.name << ' ' << x.product_code << '\n';
  }
}