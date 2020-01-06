// greet_padded.cpp
// Print a framed greeting with the padding inside the frame as a variable,
// using a string of spaces to print the spaces rather than individual space
// characters.

#include <iostream>
#include <string>

int main() {
  const int pad = 1;

  std::string name;
  std::cout << "Enter a name: ";
  std::cin >> name;
  std::cout << std::endl;

  const std::string greeting = "Hello, " + name + "!";
  const int nrow = 2 * pad + 3;
  const std::string::size_type ncol = greeting.size() + 2 * pad + 2;

  for (int r = 0; r < nrow; r++) {
    std::string::size_type c = 0;
    while (c < ncol) {
      if (r == pad + 1 && c == pad + 1) {
        std::cout << greeting;
        c += greeting.size();
      } else {
        if (r == 0 || r == nrow - 1 || c == 0 || c == ncol - 1) {
          std::cout << "*";
          c++;
        } else {
          if (r == pad + 1) {
            // Print the padding in the greeting row.
            std::cout << std::string(pad, ' ');
            c += pad;
          } else {
            // Print the blanks in a padding row.
            std::cout << std::string(ncol - 2, ' ');
            c += ncol - 2;
          }
        }
      }
    }
    std::cout << std::endl;
  }
}
