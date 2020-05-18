#include "container.hpp"
#include <stdexcept>

const double &List_container::operator[](std::size_t i) const {
  for (const auto &x : ld) {
    if (i == 0) {
      return x;
    }
    --i;
  }
  throw std::out_of_range{"list container"};
}
