// character_types.cpp
// Illustrates the use of functions to check character types.

#include <iostream>
#include <vector>

int main() {
  std::vector<char> v = {' ', 'a', 'A', '1'};
  std::cout << std::boolalpha;
  for (char c : v) {
    std::cout << "c = '" << c << "':\n"
              << "isspace(c) = " << isspace(c) << "\n"
              << "isalpha(c) = " << isalpha(c) << "\n"
              << "isupper(c) = " << isupper(c) << "\n"
              << "islower(c) = " << islower(c) << "\n"
              << "isdigit(c) = " << isdigit(c) << "\n"
              << "isalnum(c) = " << isalnum(c) << "\n\n";
  }
}
