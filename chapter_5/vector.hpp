#include <memory>

class Vector {
 public:
  explicit Vector(std::size_t);
  Vector(std::initializer_list<double>);  // Initialize with a list of doubles
  Vector(const Vector &);
  Vector(Vector &&) noexcept;
  ~Vector();

  Vector &operator=(const Vector &);
  Vector &operator=(Vector &&) noexcept;

  double &operator[](std::size_t i);
  const double &operator[](std::size_t i) const;
  [[nodiscard]] std::size_t size() const;

  void push_back(double);  // Add element at end, increasing the size by one

 private:
  std::unique_ptr<double[]> elem;  // elem points to an array of sz doubles
  std::size_t sz;
};

class Vector_size_mismatch : std::exception {};

Vector operator+(const Vector &a, const Vector &b);