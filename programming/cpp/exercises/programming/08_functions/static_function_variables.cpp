// static_function_variables.cpp
// Illustrates the use of static function variables.

#include <iostream>

class C {
public:
  C(const std::string &name) : name_(name) {
    std::cout << "construct: " << name_ << "\n";
  }
  ~C() { std::cout << "destruct: " << name_ << "\n"; }

private:
  std::string name_;
};

void f() {
  static int i = 1;
  static C x("f::x");

  std::cout << "f[" << i << "]"
            << "\n";
  i += 1;
}

int main() {
  for (int i = 0; i < 5; ++i) {
    f();
  }
}
