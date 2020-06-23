// inheritance_example.cpp
// Illustrates some aspects of class inheritance.

#include <iostream>
#include <string>

class C0 {
public:
  std::string f1() const { return "C0::f1"; }
  virtual std::string f2() const { return "C0::f2"; }
  virtual std::string f3() const { return "C0::f3"; }
  virtual std::string f4() const = 0;
};

class C1 : public C0 {
public:
  std::string f1() const { return "C1::f1"; }
  std::string f2() const override { return "C1::f2"; }
  std::string f4() const override { return "C1::f4"; }
  std::string f5() const { return "C1::f5"; }
};

int main() {
  C1 x;
  C0 *p = &x;

  // f1 is not marked virtual in C0 and is defined (but not overridden) in C1.
  // Therefore, p->f1() calls C0::f1 and x.f1() calls C1::f1.
  std::cout << "p->f1(): " << p->f1() << ", "
            << "x.f1(): " << x.f1() << std::endl;

  // f2 is marked virtual in C0 and overridden in C1.
  // Therefore, p->f2() and x.f2() both call C1::f2.
  std::cout << "p->f2(): " << p->f2() << ", "
            << "x.f2(): " << x.f2() << std::endl;

  // f3 is marked virtual in C0, but is not overridden in C1.
  // Therefore, p->f3() and x.f3() both call C0::f3.
  std::cout << "p->f3(): " << p->f3() << ", "
            << "x.f3(): " << x.f3() << std::endl;

  // f4 is marked pure virtual in C0 and overridden in C1.
  // Therefore, p->f4() and x.f4() both call C1::f4.
  // Moreover, it was necessary that C1 override f4 in order for C1 to be a
  // concrete class and allow us to create the object x of class C1.
  std::cout << "p->f4(): " << p->f4() << ", "
            << "x.f4(): " << x.f4() << std::endl;

  // f5 is defined in C1, but not in C0.
  // Therefore, p->f5() does not compile and x.f5() calls C1::f5.
  std::cout << "p->f5():    n/a, "
            << "x.f5(): " << x.f5() << std::endl;
}
