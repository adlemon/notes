// namespaces.cpp
// Illustrates the use of namespaces.

#include <iostream>

namespace NS1 {
int x = 1;
}

namespace NS2 {
int x = 2;
}

int main() {
  std::cout << "NS1::x = " << NS1::x << "\n";
  std::cout << "NS2::x = " << NS2::x << "\n";
}
