// greet_padded.cpp
// Print a framed greeting with the padding inside the frame specified by the
// user.

#include <iostream>
#include <string>

int main() {
  std::string name;
  std::cout << "Enter a name: ";
  std::cin >> name;

  int pad;
  std::cout << "Enter the padding: ";
  std::cin >> pad;

  const std::string greeting = "Hello, " + name + "!";
  const int nrow = 2 * pad + 3;
  const std::string::size_type ncol = greeting.size() + 2 * pad + 2;

  std::cout << std::endl;
  for (int r = 0; r < nrow; r++) {
    std::string::size_type c = 0;
    while (c < ncol) {
      if (r == pad + 1 && c == pad + 1) {
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
