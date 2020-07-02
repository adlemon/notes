// array_initialization.cpp
// Illustrates the initialization of arrays.

#include <iostream>

std::ostream &print_array(std::ostream &os, int arr[], int n);

int main() {
  int arr1[5];
  for (int i = 0; i < 5; ++i) {
    arr1[i] = i;
  }
  print_array(std::cout << "arr1 = ", arr1, sizeof(arr1) / sizeof(arr1[0]))
      << "\n";

  int arr2[] = {1, 2, 3};
  print_array(std::cout << "arr2 = ", arr2, 3) << "\n";
}

std::ostream &print_array(std::ostream &os, int arr[], int n) {
  os << "{";
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << arr[i];
  }
  return os << "}";
}
