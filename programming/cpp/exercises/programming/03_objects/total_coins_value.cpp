// total_coins_value.cpp
// Read the numbers of coins from the standard input and print the total value
// of the coins to the standard output.

#include <iostream>

int main() {
  int num_pennies;
  std::cout << "Enter the number of pennies: ";
  std::cin >> num_pennies;

  int num_nickels;
  std::cout << "Enter the number of nickels: ";
  std::cin >> num_nickels;

  int num_dimes;
  std::cout << "Enter the number of dimes: ";
  std::cin >> num_dimes;

  int num_quarters;
  std::cout << "Enter the number of quarters: ";
  std::cin >> num_quarters;

  int num_half_dollars;
  std::cout << "Enter the number of half dollars: ";
  std::cin >> num_half_dollars;

  int num_dollars;
  std::cout << "Enter the number of dollars: ";
  std::cin >> num_dollars;

  int num_after_half_dollars = num_dollars;
  int num_after_quarters = num_half_dollars + num_after_half_dollars;
  int num_after_dimes = num_quarters + num_after_quarters;
  int num_after_nickels = num_dimes + num_after_dimes;
  int num_after_pennies = num_nickels + num_after_nickels;

  int total_cents = 0;
  std::cout << "\nThe total value of\n";

  if (num_pennies == 1) {
    std::cout << "1 penny";
  }
  if (num_pennies > 1) {
    std::cout << num_pennies << " pennies";
  }
  if (num_pennies > 0) {
    if (num_after_pennies > 0) {
      if (num_after_nickels > 0) {
        std::cout << ",\n";
      }
      if (num_after_nickels == 0) {
        std::cout << ", and\n";
      }
    }
    if (num_after_pennies == 0) {
      std::cout << "\n";
    }
  }
  total_cents += num_pennies;

  if (num_nickels == 1) {
    std::cout << "1 nickel";
  }
  if (num_nickels > 1) {
    std::cout << num_nickels << " nickels";
  }
  if (num_nickels > 0) {
    if (num_after_nickels > 0) {
      if (num_after_dimes > 0) {
        std::cout << ",\n";
      }
      if (num_after_dimes == 0) {
        std::cout << ", and\n";
      }
    }
    if (num_after_nickels == 0) {
      std::cout << "\n";
    }
  }
  total_cents += 5 * num_nickels;

  if (num_dimes == 1) {
    std::cout << "1 dime";
  }
  if (num_dimes > 1) {
    std::cout << num_dimes << " dimes";
  }
  if (num_dimes > 0) {
    if (num_after_dimes > 0) {
      if (num_after_quarters > 0) {
        std::cout << ",\n";
      }
      if (num_after_quarters == 0) {
        std::cout << ", and\n";
      }
    }
    if (num_after_dimes == 0) {
      std::cout << "\n";
    }
  }
  total_cents += 10 * num_dimes;

  if (num_quarters == 1) {
    std::cout << "1 quarter";
  }
  if (num_quarters > 1) {
    std::cout << num_quarters << " quarters";
  }
  if (num_quarters > 0) {
    if (num_after_quarters > 0) {
      if (num_after_half_dollars > 0) {
        std::cout << ",\n";
      }
      if (num_after_half_dollars == 0) {
        std::cout << ", and\n";
      }
    }
    if (num_after_quarters == 0) {
      std::cout << "\n";
    }
  }
  total_cents += 25 * num_quarters;

  if (num_half_dollars == 1) {
    std::cout << "1 half-dollar";
  }
  if (num_half_dollars > 1) {
    std::cout << num_half_dollars << " half-dollars";
  }
  if (num_half_dollars > 0) {
    if (num_after_half_dollars > 0) {
      std::cout << ", and\n";
    }
    if (num_after_half_dollars == 0) {
      std::cout << "\n";
    }
  }
  total_cents += 50 * num_half_dollars;

  if (num_dollars == 1) {
    std::cout << "1 dollar\n";
  }
  if (num_dollars > 1) {
    std::cout << num_dollars << " dollars\n";
  }
  total_cents += 100 * num_dollars;

  int formatted_dollars = total_cents / 100;
  int formatted_cents = total_cents % 100;

  std::cout << "is ";
  if (formatted_dollars > 0) {
    std::cout << formatted_dollars << " dollars";
    if (formatted_cents > 0) {
      std::cout << " and " << formatted_cents << " cents.\n";
    }
    if (formatted_cents == 0) {
      std::cout << " even.\n";
    }
  }
  if (formatted_dollars == 0) {
    if (formatted_cents > 0) {
      std::cout << formatted_cents << " cents.\n";
    }
    if (formatted_cents == 0) {
      std::cout << " nothing.\n";
    }
  }
}
