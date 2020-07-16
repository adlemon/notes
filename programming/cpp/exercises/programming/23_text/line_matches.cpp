// line_matches.cpp
// Read a filename and a regular expression from the user. Then print the line
// numbers and corresponding lines for all lines in the file that match the
// regular expression.

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <typeinfo>

int main() {
  std::string infilename;
  std::cout << "Enter the name of the file: ";
  std::cin >> infilename;

  std::ifstream infile{infilename};
  if (!infile) {
    std::cerr << "unable to open input file: " << infilename << "\n";
    return 1;
  }

  std::regex regex_pattern;
  std::string regex_pattern_str;
  try {
    std::cout << "Enter the regular expression to match: ";
    std::cin >> regex_pattern_str;
    regex_pattern = regex_pattern_str;
  } catch (...) {
    std::cerr << "invalid regular expression: " << regex_pattern_str << "\n";
    return 2;
  }

  size_t line_number = 0;
  for (std::string line; std::getline(infile, line);) {
    ++line_number;
    std::smatch regex_matches;
    if (regex_match(line, regex_matches, regex_pattern)) {
      std::cout << "[" << line_number << "]: " << line << "\n";
    }
  }
}
