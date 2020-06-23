// default_constructors.cpp
// Illustrates the use of a default constructor.

#include <iostream>
#include <string>
#include <vector>

class C1 {
public:
  C1(const std::string &name) : name_(name) {}

private:
  std::string name_;
};

class C2 {
public:
  C2() : name_("no name") {}
  C2(const std::string &name) : name_(name) {}

private:
  std::string name_;
};

int main() {
  // The line below fails because v1 does not have a default constructor.
  // std::vector<C1> v1(10);
  // The line below succeeds because v2 does have a default constructor.
  std::vector<C2> v2(10);
}
