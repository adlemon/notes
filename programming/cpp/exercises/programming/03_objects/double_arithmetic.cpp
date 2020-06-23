// double_arithmetic.cpp
// Reads an arithmetic operation and two doubles from the standard input and
// prints the result of the arithmetic operation to the standard output.

#include <iostream>
#include <string>

int main() {
  std::string op;
  std::cout << "Enter an arithmetic operation on doubles "
            << "(+, plus, -, minus, *, mult, /, or div): ";
  std::cin >> op;

  double d1, d2;
  std::cout << "Enter two doubles: ";
  std::cin >> d1 >> d2;

  if (op == "+") {
    std::cout << d1 << " + " << d2 << " = " << d1 + d2 << ".\n";
  }
  if (op == "plus") {
    std::cout << "plus(" << d1 << ", " << d2 << ") = " << d1 + d2 << ".\n";
  }
  if (op == "-") {
    std::cout << d1 << " - " << d2 << " = " << d1 - d2 << ".\n";
  }
  if (op == "minus") {
    std::cout << "minus(" << d1 << ", " << d2 << ") = " << d1 - d2 << ".\n";
  }
  if (op == "*") {
    std::cout << d1 << " * " << d2 << " = " << d1 * d2 << ".\n";
  }
  if (op == "mult") {
    std::cout << "mult(" << d1 << ", " << d2 << ") = " << d1 * d2 << ".\n";
  }
  if (op == "/") {
    std::cout << d1 << " / " << d2 << " = " << d1 / d2 << ".\n";
  }
  if (op == "div") {
    std::cout << "div(" << d1 << ", " << d2 << ") = " << d1 / d2 << ".\n";
  }
}
