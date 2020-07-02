// initializer_list.cpp
// Illustrates a constructor that uses an initializer list.

#include <initializer_list>
#include <iostream>

class C {
public:
  C(std::initializer_list<int> lst);
};

int main() {
  C{1};
  C{1, 2};
  C{1, 2, 3};
  C{1, 2, 3, 4};
  C{1, 2, 3, 4, 5};
}

C::C(std::initializer_list<int> lst) {
  std::cout << "C constructor given initializer list:\n";
  for (int i : lst) {
    std::cout << i << "\n";
  }
  std::cout << "\n";
}
