// get_io.cpp
// Demonstrates the use of get and getline for input streams.

#include <iostream>
#include <string>

int main() {
  char c;
  std::cout << "Enter some text: ";
  while (std::cin.get(c)) {
    if (c == '\n') {
      break;
    }
    std::cout << c << "\n";
  }

  std::string s;
  std::cout << "\nEnter some text: ";
  std::getline(std::cin, s);
  std::cout << "read: " << s << "\n";
}
