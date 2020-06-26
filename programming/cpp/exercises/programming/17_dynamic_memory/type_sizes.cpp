// type_sizes.cpp
// Print the sizes of various types.

#include <iostream>
#include <string>

class C0 {};
class C1 {
  char c1;
};
class C2 {
  char c1, c2;
};
class C3 {
  char c1, c2, c3;
};
class C4 {
  char c1, c2, c3, c4;
};
class C5 {
  char c1, c2, c3, c4, c5;
};

int main() {
  std::cout << "sizeof(char)   = " << sizeof(char) << "\n"
            << "sizeof('0')    = " << sizeof('0') << "\n"
            << "sizeof(int)    = " << sizeof(int) << "\n"
            << "sizeof(0)      = " << sizeof(0) << "\n"
            << "sizeof(double) = " << sizeof(double) << "\n"
            << "sizeof(0.0)    = " << sizeof(0.0) << "\n";

  std::string s("x");
  for (int i = 0; i < 8; ++i) {
    s += s;
    std::cout << "sizeof(std::string with " << s.size()
              << " characters) = " << sizeof(s) << "\n";
  }

  std::cout << "sizeof(class with 0 members)      = " << sizeof(C0) << "\n"
            << "sizeof(class with 1 char member)  = " << sizeof(C1) << "\n"
            << "sizeof(class with 2 char members) = " << sizeof(C2) << "\n"
            << "sizeof(class with 3 char members) = " << sizeof(C3) << "\n"
            << "sizeof(class with 4 char members) = " << sizeof(C4) << "\n"
            << "sizeof(class with 5 char members) = " << sizeof(C5) << "\n";
}
