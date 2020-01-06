// greet_padded_2d.cpp
// Print a framed greeting with different variables for the vertical and
// horizontal paddings.

#include <iostream>
#include <string>

int main() {
  const int vpad = 1;
  const int hpad = 2;

  std::string name;
  std::cout << "Enter a name: ";
  std::cin >> name;
  std::cout << std::endl;

  const std::string greeting = "Hello, " + name + "!";
  const int nrow = 2 * vpad + 3;
  const std::string::size_type ncol = greeting.size() + 2 * hpad + 2;

  for (int r = 0; r < nrow; r++) {
    std::string::size_type c = 0;
    while (c < ncol) {
      if (r == vpad + 1 && c == hpad + 1) {
        std::cout << greeting;
        c += greeting.size();
      } else {
        if (r == 0 || r == nrow - 1 || c == 0 || c == ncol - 1) {
          std::cout << "*";
        } else {
          std::cout << " ";
        }
        c++;
      }
    }
    std::cout << std::endl;
  }
}
