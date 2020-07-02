// copy_and_move.cpp
// Illustrates copy and move operations.

#include <iostream>

class C {
public:
  C() { std::cout << "default constructor\n"; }
  C(int i) : i_(i) {
    std::cout << "constructor called with argument: " << i << "\n";
  }
  C(const C &other) {
    std::cout << "copy constructor called with other.i_ = " << other.i_ << "\n";
    i_ = other.i_;
  }
  C &operator=(const C &other) {
    std::cout << "copy assignment called with other.i_ = " << other.i_ << "\n";
    i_ = other.i_;
    return *this;
  }
  C(const C &&other) {
    std::cout << "move constructor called with other.i_ = " << other.i_ << "\n";
    i_ = other.i_;
  }
  C &operator=(const C &&other) {
    std::cout << "move assignment called with other.i_ = " << other.i_ << "\n";
    i_ = other.i_;
    return *this;
  }

private:
  int i_;
};

int main() {
  std::cout << "C c1;\n";
  C c1;

  std::cout << "\nC c2(2);\n";
  C c2(2);

  std::cout << "\nC c3(c2);\n";
  C c3(c2);

  std::cout << "\nC c4 = c3;\n";
  C c4 = c2;

  std::cout << "\nc1 = c2;\n";
  c1 = c2;

  std::cout << "\nC c5(C(5));\n";
  C c5(C(5));

  std::cout << "\nC c6 = std::move(c5);\n";
  C c6 = std::move(c5);

  std::cout << "\nc6 = std::move(c4);\n";
  c6 = std::move(c4);
}
