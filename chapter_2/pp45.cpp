#include <iostream>

enum class Traffic_light { green, yellow, red };

// Definition of an operator for Traffic_light
Traffic_light &operator++(Traffic_light &t) // prefix increment: ++
{
  switch (t) {
  case Traffic_light::green:
    return t = Traffic_light::yellow;
  case Traffic_light::yellow:
    return t = Traffic_light::red;
  case Traffic_light::red:
    return t = Traffic_light::green;
  }
}

int main() {
  Traffic_light light = Traffic_light::red;
  Traffic_light next = ++light; // next becomes Traffic_light::green
  std::cout << static_cast<int>(next) << '\n';

  if (Traffic_light::green < Traffic_light::red) {
    std::cout << "Enumerators can be compared.\n";
  }

  //////////////////////////////////////////////////////////////////////////////
  // The class after the enum specifies that its enumerators are scoped and
  // strongly type.
  enum class Color { red, blue, green };

  Color col = Color::red;
  // Color c = 2; // Initialization error: 2 is not a Color
  Color c{2};

  // int i = Color::red; // Error: Color::red is not an int
  int i = static_cast<int>(Color::red);

  std::cout << static_cast<int>(col) << static_cast<int>(c) << i << '\n';

  //////////////////////////////////////////////////////////////////////////////

  // These enumerators are not scoped
  enum Color2 { red, blue, green };
  Color2 d = red;
  // Color2 e{2}; // Error: Cannot initialize Color2 with an int
  int j = red; // Implicitly converts to integer

  std::cout << d << j << '\n';
}