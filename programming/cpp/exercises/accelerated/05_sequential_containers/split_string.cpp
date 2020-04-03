// split_string.cpp
// Read a line of input from the user and split it into words.

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split_string(const std::string &s);

int main() {
  std::string line;
  std::cout << "Enter a line of text: ";
  getline(std::cin, line);

  std::vector<std::string> words = split_string(line);
  std::cout << "\nThe words in the line are:\n";
  for (std::vector<std::string>::const_iterator it = words.begin();
       it < words.end(); ++it) {
    std::cout << *it << '\n';
  }
}

std::vector<std::string> split_string(const std::string &s) {
  std::vector<std::string> words;

  std::string::size_type i = 0;
  while (i < s.size()) {
    while (i < s.size() && std::isspace(s[i])) {
      i++;
    }

    std::string::size_type j = i;
    while (j < s.size() && !std::isspace(s[j])) {
      j++;
    }

    if (j > i) {
      words.push_back(s.substr(i, j - i));
    }
    i = j;
  }

  return words;
}
