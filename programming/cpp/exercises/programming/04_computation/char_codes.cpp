// char_codes.cpp
// Print a table showing the numeric codes for letters and digits.

#include <iomanip>
#include <iostream>

void print_character_range(char begin, char end);

int main() {
  print_character_range('0', '9');
  print_character_range('A', 'Z');
  print_character_range('a', 'z');
}

void print_character_range(char begin, char end) {
  for (char c = begin; c <= end; ++c) {
    std::cout << "The code for the char '" << c << "' is " << std::setw(3)
              << int(c) << ".\n";
  }
}
