// digit_to_string.cpp
// Read a single digit as an integer, and then print the digit as written in
// English. For example, if the program reads the digit 1, it will print "one".

#include <iostream>
#include <string>
#include <vector>

std::string digit_to_string_switch(int digit);
std::string digit_to_string_vector(int digit);

int main() {
  int digit = -1;
  std::cout << "Enter a single digit (0-9): ";
  std::cin >> digit;

  if (!(0 <= digit && digit <= 9)) {
    std::cout << "\nYou did not enter a single digit.\n";
    return 1;
  }

  std::cout << "\nAccording to the function that uses switch:\n"
            << "in English, the digit " << digit << " is spelled \""
            << digit_to_string_switch(digit) << "\".\n";
  std::cout << "\nAccording to the function that uses a vector:\n"
            << "in English, the digit " << digit << " is spelled \""
            << digit_to_string_vector(digit) << "\".\n";
}

std::string digit_to_string_switch(int digit) {
  switch (digit) {
  case 0:
    return "zero";
    break;
  case 1:
    return "one";
    break;
  case 2:
    return "two";
    break;
  case 3:
    return "three";
    break;
  case 4:
    return "four";
    break;
  case 5:
    return "five";
    break;
  case 6:
    return "six";
    break;
  case 7:
    return "seven";
    break;
  case 8:
    return "eight";
    break;
  case 9:
    return "nine";
    break;
  default:
    return "";
  }
}
std::string digit_to_string_vector(int digit) {
  static const std::vector<std::string> digit_spellings{
      "zero", "one", "two",   "three", "four",
      "five", "six", "seven", "eight", "nine"};
  return digit_spellings[digit];
}
