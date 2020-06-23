// decimal_octal_hexadecimal.cpp
// Print numbers in different bases.

#include <iostream>
#include <vector>

void print_integer_in_bases(int x) {
  std::cout << std::showbase << "decimal:     " << std::dec << x << "\n"
            << "octal:       " << std::oct << x << "\n"
            << "hexadecimal: " << std::hex << x << "\n\n";
}

int main() {
  std::vector<int> v = {2222, 02222, 0x2222};
  for (int x : v) {
    print_integer_in_bases(x);
  }

  std::cout << "Enter an integer: ";
  std::cin.unsetf(std::ios::dec);
  std::cin.unsetf(std::ios::oct);
  std::cin.unsetf(std::ios::hex);
  int x;
  std::cin >> x;
  print_integer_in_bases(x);
}
