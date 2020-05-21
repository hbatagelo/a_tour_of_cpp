#include "shape.hpp"

std::unique_ptr<Shape> read_shape(std::istream &is) {
  int r{};
  is >> r;
  return std::make_unique<Circle>(Point{r, r}, r);
}