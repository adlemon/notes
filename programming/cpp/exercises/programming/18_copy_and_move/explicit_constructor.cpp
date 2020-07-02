// explicit_constructor.cpp
// Illustrates the use of an explicit constructor.

#include <iostream>

class C1 {
public:
  C1(int i) : i_(i) {}
  int i() { return i_; }

private:
  int i_;
};

class C2 {
public:
  explicit C2(int i) : i_(i) {}

private:
  int i_;
};

int main() {
  C1 c1 = 1;
  std::cout << "c1.i() = " << c1.i() << "\n";

  // The following line does not compile because the constructor C2(int i) is
  // marked explicit.
  // C2 c2 = 2;
}
