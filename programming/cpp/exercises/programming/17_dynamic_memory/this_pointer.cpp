// this_pointer.cpp
// Illustrate the use of the this pointer in a member function.

#include <iostream>

class C {
public:
  C(int x) : x_(x) {}
  bool is_same(C *p) { return p == this; }

private:
  int x_;
};

int main() {
  C *c1a = new C{1};
  C *c1b = new C{1};
  C *c2a = new C{2};

  std::cout << "c1a->is_same(c1a) = " << c1a->is_same(c1a) << "\n"
            << "c1a->is_same(c1b) = " << c1a->is_same(c1b) << "\n"
            << "c1a->is_same(c2a) = " << c1a->is_same(c2a) << "\n";
}
