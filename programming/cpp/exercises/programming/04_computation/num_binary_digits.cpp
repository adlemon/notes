// num_binary_digits.cpp
// Print the number of binary digits needed to represent 1'000, 1'000'000, and
// 1'000'000'000.

#include <iostream>

int main() {
  int target = 1000;

  int binary_digit_value = 1;
  int num_binary_digits = 1;
  int sum_binary_digits = 1;
  while (true) {
    binary_digit_value *= 2;
    num_binary_digits += 1;
    sum_binary_digits += binary_digit_value;

    if (sum_binary_digits >= target) {
      std::cout << "It takes " << num_binary_digits
                << " binary digits to represent " << target << ".\n";

      // Multiplying 1'000'000'000 results in an integer overflow, so we
      // determine when to end the loop using a break statement inside the loop
      // rather than the loop predicate.
      if (target == 1'000'000'000) {
        break;
      } else {
        target *= 1000;
      }
    }
  }
}
