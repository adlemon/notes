// change_case.cpp
// Read a line from the user and then print the line in lowercase and uppercase.

#include <iostream>
#include <sstream>
#include <string>

std::string apply_to_characters(const std::string &s, int fun(int));
std::string tolower(const std::string &s);
std::string toupper(const std::string &s);

int main() {
  std::string s;
  std::cout << "Enter some text: ";
  getline(std::cin, s);

  std::cout << "\nIn lowercase your text is: " << tolower(s) << "\n"
            << "In uppercase your text is: " << toupper(s) << "\n";
}

std::string apply_to_characters(const std::string &s, int fun(int)) {
  std::string t(s);
  for (std::string::size_type i = 0; i < t.size(); ++i) {
    t[i] = fun(t[i]);
  }
  return t;
}

std::string tolower(const std::string &s) {
  return apply_to_characters(s, tolower);
}

std::string toupper(const std::string &s) {
  return apply_to_characters(s, toupper);
}
