// class_template.cpp
// Illustrates the use of a class template.

#include <iostream>

template <class T> class C {
public:
  C(T x) : x_(x) {}
  T x() { return x_; }
  void set(T x) { x_ = x; }

private:
  T x_;
};

int main() {
  C<int> c1(1);
  std::cout << "c1.x() = " << c1.x() << "\n";

  C<double> c2(2.2);
  std::cout << "c2.x() = " << c2.x() << "\n";
}
