#include <memory>

class Vector {
public:
  explicit Vector(std::size_t s);

  double &operator[](std::size_t i);
  [[nodiscard]] std::size_t size() const;

private:
  std::unique_ptr<double[]> elem; // elem points to an array of sz doubles
  std::size_t sz;
};