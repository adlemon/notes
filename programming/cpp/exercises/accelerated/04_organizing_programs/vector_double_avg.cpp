// vector_double_avg.cpp
// Write and use a function that computes the average of a vector of doubles.

#include <iostream>
#include <vector>

double average(std::vector<double> v);

int main() {
  std::vector<double> v;
  double x;
  std::cout << "Enter the doubles and end-of-file when done: ";
  while (std::cin >> x) {
    v.push_back(x);
  }

  std::cout << '\n'
            << "The average of the values that were entered is: "
            << average(v)
            << '\n';
}

double average(std::vector<double> v) {
  double sum = 0;
  for (std::vector<double>::size_type i = 0; i < v.size(); i++) {
    sum += v[i];
  }
  return sum / v.size();
}
