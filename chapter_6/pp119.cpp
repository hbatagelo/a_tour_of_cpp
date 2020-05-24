#include <vector>
#include "shape.hpp"

// template<Sequence C, Callable Oper>
// Assume C is a container of pointers
template <typename C, typename Oper>
void for_all(C& c, Oper op) {
  for (auto& x : c) {
    op(x);  // Pass op() a reference to each element pointed to
  }
}

template <typename S>
void rotate_and_draw(std::vector<S>& v, int r) {
  // Generic lambda
  for_all(v, [&r](auto& s) {  // Errata: missing capture in pp.120
    s->rotate(r);
    s->draw();
    std::cout << r << '\n';
  });
}

void user2() {
  std::vector<std::unique_ptr<Shape>> v;
  v.push_back(read_shape(std::cin));
  for_all(v, [](std::unique_ptr<Shape>& ps) { ps->draw(); });
  for_all(v, [](std::unique_ptr<Shape>& ps) { ps->rotate(45); });
  for_all(v, [](auto& ps) { std::cout << ps->center().x << '\n'; });

  rotate_and_draw(v, 10);
}

int main() {
  user2();
}