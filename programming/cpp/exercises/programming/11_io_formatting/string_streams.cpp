// string_streams.cpp
// Illustrates the use of string streams.

#include <iostream>
#include <sstream>

int main() {
  std::stringstream ss("2.71");
  double x;
  ss >> x;
  std::cout << "x = " << x << "\n";

  ss.clear();
  ss << "Hello";
  ss << ", World!";
  std::cout << "ss.str() = " << ss.str() << "\n";
}
