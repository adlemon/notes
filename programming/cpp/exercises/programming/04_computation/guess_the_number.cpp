// guess_the_number.cpp
// Guesses a number between 1 and 100 chosen by the user.

#include <iostream>

int main() {
  int lo = 1, hi = 100;

  std::cout << "Think of a number between 1 and 100 inclusive.\n";
  while (lo < hi) {
    int md = (lo + hi) / 2;
    std::cout << "\nI guess that your number is " << md << ".\n"
              << "Is the guess\n"
              << "(1) too low,\n"
              << "(2) too high, or\n"
              << "(3) correct?\n"
              << "Choose one: ";

    int answer;
    std::cin >> answer;
    switch (answer) {
    case 1:
      lo = md + 1;
      break;
    case 2:
      hi = md - 1;
      break;
    case 3:
      lo = hi = md;
      break;
    default:
      std::cout << "Invalid choice.\n";
    }
  }

  std::cout << "\nYour number is " << lo << ".\n";
}
