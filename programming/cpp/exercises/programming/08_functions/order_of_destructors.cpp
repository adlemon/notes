// order_of_destructors.cpp
// Illustrates the order in which destructors are called for scoped variables.

#include <iostream>
#include <string>

class C {
public:
  C(const std::string &name) : name_(name) {
    std::cout << "construct: " << name_ << "\n";
  }
  ~C() { std::cout << "destruct: " << name_ << "\n"; }

private:
  std::string name_;
};

int main() {
  C x("x");
  C y("y");
}
