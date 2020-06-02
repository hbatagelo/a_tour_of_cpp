#include <bitset>
#include <iostream>

void binary(uint i) {
  std::bitset<8 * sizeof(int)> b{i};   // Assume 8-bit byte
  std::cout << b.to_string() << '\n';  // Write out the bits of i
}

void binary2(uint i) {
  std::bitset<8 * sizeof(int)> b{i};  // Assume 8-bit byte
  std::cout << b << '\n';             // Write out the bits of i
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  std::bitset<9> bs1{"110001111"};
  std::bitset<9> bs2{0b1'1000'1111};
  std::bitset<9> bs3 = ~bs1;       // Complement: bs3="001110000"
  std::bitset<9> bs4 = bs1 & bs3;  // All zeros
  std::bitset<9> bs5 = bs1 << 2;   // Shift left: bs5 = "000111100"
  std::cout << bs1 << '\n';
  std::cout << bs2 << '\n';
  std::cout << bs3 << '\n';
  std::cout << bs4 << '\n';
  std::cout << bs5 << '\n';

  binary(255);
  binary2(65535);
}