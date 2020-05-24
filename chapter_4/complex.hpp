class complex {
  double re{}, im{};

 public:
  complex(double r, double i) : re{r}, im{i} {}
  explicit complex(double r) : re{r} {}
  complex() = default;

  [[nodiscard]] double real() const { return re; }
  void real(double d) { re = d; }
  [[nodiscard]] double imag() const { return im; }
  void imag(double d) { im = d; }

  complex &operator+=(complex z) {
    re += z.re;
    im += z.im;
    return *this;
  }

  complex &operator-=(complex z) {
    re -= z.re;
    im -= z.im;
    return *this;
  }

  complex &operator*=(complex);
  complex &operator/=(complex);
};

complex operator+(complex a, complex b);
complex operator-(complex a, complex b);
complex operator-(complex a);
complex operator*(complex a, complex b);
complex operator/(complex a, complex b);
bool operator==(complex a, complex b);
bool operator!=(complex a, complex b);
