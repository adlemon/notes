// function_template.cpp
// Illustrates the use of a function template.

#include <iostream>

template <class T> T multiply_2(T x) { return 2 * x; }

int main() {
  std::cout << "multiply_2(2) = " << multiply_2(2) << "\n"
            << "multiply_2(3.0) = " << multiply_2(3.0) << "\n"
            << "multiply_2<double>(4) = " << multiply_2(4) << "\n";
}
