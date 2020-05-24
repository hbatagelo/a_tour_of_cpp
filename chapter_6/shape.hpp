#include <iostream>
#include <memory>

struct Point {
  int x{};
  int y{};
};

class Shape {
 public:
  [[nodiscard]] virtual Point center() const = 0;
  virtual void move(Point to) = 0;
  virtual void draw() const = 0;
  virtual void rotate(int angle) = 0;
  virtual ~Shape() = default;

 protected:
  Shape() = default;
  Shape(const Shape&) = default;
  Shape(Shape&&) noexcept = default;
  Shape& operator=(const Shape&) = default;
  Shape& operator=(Shape&&) = default;
};

class Circle : public Shape {
 public:
  Circle(Point p, int rad) : pt{p}, r{rad} {};
  [[nodiscard]] Point center() const override { return pt; };
  void move(Point to) override { pt = to; };
  void draw() const override{};
  void rotate([[maybe_unused]] int angle) override{};
  [[nodiscard]] int radius() const { return r; }

 private:
  Point pt{};
  int r{};
};

std::unique_ptr<Shape> read_shape(std::istream& is);