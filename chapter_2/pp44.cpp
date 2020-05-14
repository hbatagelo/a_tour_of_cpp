#include <iostream>
#include <variant>

/*
// pp.43

enum Type { ptr, num };

struct Entry {
  std::string name;

  union Value {
    Node *p;
    int i;
  } v;

  Type t;
};

void f(Entry *pe) {
  if (pe->t == num) {
    std::cout << pe->v.i;
  }
}
*/

struct Node {
  int x;
};

struct Entry {
  std::string name;
  std::variant<Node *, int> v;
};

void f(Entry *pe) {
  // Does *pe hold an int?
  if (std::holds_alternative<int>(pe->v)) {
    // Get the int
    std::cout << std::get<int>(pe->v) << '\n';
  } else {
    std::cout << std::get<Node *>(pe->v)->x << '\n';
  }
}

int main() {
  Entry a{.name{"Entry a"}, .v = 42};
  f(&a);

  Node n{100};
  Entry b{.name{"Entry b"}, .v = &n};
  f(&b);
}