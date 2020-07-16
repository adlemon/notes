// to_from_string.cpp
// Demonstrate functions for converting to and from strings.

#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

template <typename T> std::string to_string(const T &t);
template <typename T> T from_string(const std::string &s);

int main() {
  {
    int x = 1;
    std::string s = to_string(x);
    if (s == "1") {
      std::cout << "s == \"1\"\n";
    } else {
      std::cout << "s != \"1\"\n";
    }
  }

  {
    std::string s = "2";
    int x = from_string<int>(s);
    if (x == 2) {
      std::cout << "x == 2\n";
    } else {
      std::cout << "x != 2\n";
    }
  }
}

template <typename T> std::string to_string(const T &t) {
  std::ostringstream os;
  os << t;
  return os.str();
}

template <typename T> T from_string(const std::string &s) {
  std::istringstream is{s};
  T t;
  is >> t;
  return t;
}
