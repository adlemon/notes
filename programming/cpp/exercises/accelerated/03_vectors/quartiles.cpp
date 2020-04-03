// quartiles.cpp
// Read numbers from the standard input and compute the quartiles of the numbers
// that were read.

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

int main() {
  // Read the numbers.
  double x;
  std::vector<double> numbers;
  std::cout << "Enter the numbers and end-of-file when done: ";
  while (std::cin >> x) {
    numbers.push_back(x);
  }
  std::cout << "\n";

  // Sort the numbers.
  std::sort(numbers.begin(), numbers.end());

  // Handle edge cases.
  std::vector<double>::size_type n = numbers.size();
  if (n == 0) {
    std::cerr << "ERROR: Cannot compute the quartiles of an empty data set."
              << std::endl;
    return 1;
  }
  if (n == 1) {
    std::streamsize prec = std::cout.precision();
    std::cout << std::setprecision(6) << "Lower Quartile: " << numbers[0]
              << "\n"
              << "Median:         " << numbers[0] << "\n"
              << "Upper Quartile: " << numbers[0] << std::endl
              << std::setprecision(prec);
    return 0;
  }

  // Compute the quartiles.
  double lower_quartile, median, upper_quartile;
  int k = n / 4;
  switch (n % 4) {
  case 0:
    // If there are n = 4*k numbers, then we can divide the numbers into four
    // groups with k numbers each:
    //   #1: numbers[0], ..., numbers[k-1],
    //   #2: numbers[k], ..., numbers[2*k-1],
    //   #3: numbers[2*k], ..., numbers[3*k-1],
    //   #4: numbers[3*k], ..., numbers[4*k-1].
    // The lower quartile is the "dividing line" between #1 and #2: that is,
    // numbers[k-0.5], which we approximate using linear interpolation by
    lower_quartile = 0.5 * numbers[k - 1] + 0.5 * numbers[k];
    // The median is the "dividing line" between #2 and #3: that is,
    // numbers[2*k-0.5], which we approximate using linear interpolation by
    median = 0.5 * numbers[2 * k - 1] + 0.5 * numbers[2 * k];
    // The upper quartile is the "dividing line" between #3 and #4: that is,
    // numbers[3*k-0.5], which we approximate using linear interpolation by
    upper_quartile = 0.5 * numbers[3 * k - 1] + 0.5 * numbers[3 * k];
    break;
  case 1:
    // If there are n = 4*k+1 numbers, then we can divide the numbers into
    // four groups with k+0.25 numbers each:
    //   #1: numbers[0], ..., numbers[k-0.75],
    //   #2: numbers[k + 0.25], ..., numbers[2*k-0.5],
    //   #3: numbers[2*k + 0.5], ..., numbers[3*k-0.25],
    //   #4: numbers[3*k + 0.75], ..., numbers[4*k].
    // The lower quartile is the "dividing line" between #1 and #2: that is,
    // numbers[k-0.25], which we approximate using linear interpolation by
    lower_quartile = 0.25 * numbers[k - 1] + 0.75 * numbers[k];
    // The median is the "dividing line" between #2 and #3: that is,
    median = numbers[2 * k];
    // The upper quartile is the "dividing line" between #3 and #4: that is,
    // numbers[3*k+0.25], which we approximate using linear interpolation by
    upper_quartile = 0.75 * numbers[3 * k] + 0.25 * numbers[3 * k + 1];
    break;
  case 2:
    // If there are n = 4*k+2 numbers, then we can divide the numbers into
    // four groups with k+0.5 numbers each:
    //   #1: numbers[0], ..., numbers[k-0.5],
    //   #2: numbers[k+0.5], ..., numbers[2*k],
    //   #3: numbers[2*k+1], ..., numbers[3*k+0.5],
    //   #4: numbers[3*k+1.5], ..., numbers[4*k+1].
    // The lower quartile is the "dividing line" between #1 and #2: that is,
    lower_quartile = numbers[k];
    // The median is the "dividing line" between #2 and #3: that is,
    // numbers[2*k+0.5], which we approximate using linear interpolation by
    median = 0.5 * numbers[2 * k] + 0.5 * numbers[2 * k + 1];
    // The upper quartile is the "dividing line" between #3 and #4: that is,
    upper_quartile = numbers[3 * k + 1];
    break;
  case 3:
    // If there are n = 4*k+3 numbers, then we can divide the numbers into
    // four groups with k+0.75 numbers each:
    //   #1: numbers[0], ..., numbers[k-0.25],
    //   #2: numbers[k+0.75], ..., numbers[2*k+0.5],
    //   #3: numbers[2*k+1.5], ..., numbers[3*k+1.25],
    //   #4: numbers[3*k+2.25], ..., numbers[4*k+2].
    // The lower quartile is the "dividing line" between #1 and #2: that is,
    // numbers[k+0.25], which we approximate using linear interpolation by
    lower_quartile = 0.75 * numbers[k] + 0.25 * numbers[k + 1];
    // The median is the "dividing line" between #2 and #3: that is,
    median = numbers[2 * k + 1];
    // The upper quartile is the "dividing line" between #3 and #4: that is,
    // numbers[3*k+1.75], which we approximate using linear interpolation by
    upper_quartile = 0.25 * numbers[3 * k] + 0.75 * numbers[3 * k + 1];
    break;
  }

  std::streamsize prec = std::cout.precision();
  std::cout << std::setprecision(6) << "Lower Quartile: " << lower_quartile
            << "\n"
            << "Median:         " << median << "\n"
            << "Upper Quartile: " << upper_quartile << std::endl
            << std::setprecision(prec);
}
