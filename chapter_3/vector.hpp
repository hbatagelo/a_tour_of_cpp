#include <memory>

class Vector {
public:
  explicit Vector(int s);
  double &operator[](int i);
  int size() const;

private:
  std::unique_ptr<double> elem; // elem points to an array of sz doubles
  int sz;
};