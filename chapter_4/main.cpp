#include "complex.hpp"
#include "container.hpp"
#include <iostream>

void f(complex z) {
  complex a{2.3};
  complex b{complex{1} / a};
  complex c{a + z * complex{1, 2.3}};

  if (c != b) {
    c = -(b / a) + complex{2} * b;
  }
}

Vector read(std::istream &is) {
  Vector v(10);
  for (double d = 0; is >> d;) {
    v.push_back(d);
  }
  return v;
}

// The Container interface is used in complete ignorance of implementation
// details.
void use(const Container &c) {
  const auto sz = c.size();
  for (std::size_t i = 0; i != sz; ++i) {
    std::cout << c[i] << '\n';
  }
}

void g() {
  Vector_container vc(10); //	Vector of ten elements
  // ...fill	vc..
  use(vc);
}

void h() {
  List_container lc{1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::shared_ptr<List_container> a =
      std::make_shared<List_container>(std::initializer_list<double>{1, 2, 3});

  // A polymorphic object.
  // vpointer will point to List_container's vtable
  std::shared_ptr<Container> b = a;

  std::cout << "\n*b: \n";
  use(*b);

  std::cout << "\nlc: \n";
  use(lc);

  std::cout << '\n';

  // Check if b is of a List_container, or a class derived from List_container
  if (dynamic_cast<List_container *>(b.get()) != nullptr) {
    std::cout << "b is a List_container\n";
  } else {
    std::cout << "b is not a List_container\n";
  }

  // Converting Container to List_container reference
  List_container &c{dynamic_cast<List_container &>(*b)};
  std::cout << c.size() << '\n';

  // Check if lc is of a Vector, or a class derived from Vector
  if (dynamic_cast<Vector *>(&lc) != nullptr) {
    std::cout << "lc is a Vector\n";
  } else {
    std::cout << "lc is not a Vector\n";
  }
}

int main() {
  g();
  h();

  Vector v2{1.23, 3.45, 6.7, 8};

  for (std::size_t i = 0; i < v2.size(); ++i) {
    std::cout << v2[i] << '\n';
  }

  Vector v = read(std::cin);
}