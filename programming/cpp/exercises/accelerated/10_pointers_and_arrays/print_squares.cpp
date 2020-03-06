// print_squares.cpp
// Print a table of squares using function pointers.

#include <iostream>

int square(int x);
int apply_function_verbose(int (*f)(int x), int x);
int apply_function_concise(int f(int x), int x);

int main() {
  int a, b;
  std::cout << "Enter the minimum integer: ";
  std::cin >> a;
  std::cout << "Enter the maximum integer: ";
  std::cin >> b;

  for (int i = a; i <= b; ++i) {
    std::cout << i
              << " " << apply_function_verbose(square, i)
              << " " << apply_function_concise(square, i) << "\n";
  }
}

int square(int x) {
  return x * x;
}

int apply_function_verbose(int (*f)(int x), int x) {
  return f(x);
}

int apply_function_concise(int f(int x), int x) {
  return f(x);
}
