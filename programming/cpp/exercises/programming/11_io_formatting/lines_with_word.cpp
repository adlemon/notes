// lines_with_word.cpp
// Read a file and print all lines that contains a target word.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> words(const std::string &s);
bool contains(const std::vector<std::string> &v, const std::string &s);

int main() {
  std::cout << "Enter the name of the input file: ";
  std::string filename;
  std::cin >> filename;

  std::ifstream infile{filename};
  if (!infile) {
    std::cerr << "Unable to open file " << filename << " for reading.\n";
    return 1;
  }

  std::cout << "Enter the target word: ";
  std::string word;
  std::cin >> word;

  std::string line;
  unsigned line_number = 0;
  while (getline(infile, line)) {
    ++line_number;
    if (contains(words(line), word)) {
      std::cout << "[" << line_number << "]: " << line << "\n";
    }
  }
}

std::vector<std::string> words(const std::string &s) {
  std::istringstream is(s);

  std::vector<std::string> words;
  std::string word;
  while (is >> word) {
    words.push_back(word);
  }

  return words;
}

bool contains(const std::vector<std::string> &v, const std::string &s) {
  for (const std::string &t : v) {
    if (t == s) {
      return true;
    }
  }
  return false;
}
