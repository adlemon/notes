// all_lowercase_some_uppercase.cpp
// Read words from the user; after reading all of the words, print the words
// that are all lowercase followed by the words that have at least one
// uppercase letter.

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

bool all_lowercase(std::string s);
void print_words(std::vector<std::string> words);

int main() {
  std::vector<std::string> all_lowercase_words, some_uppercase_words;

  std::string word;
  std::cout << "Enter the words followed by end-of-file:\n";
  while (std::cin >> word) {
    if (all_lowercase(word)) {
      all_lowercase_words.push_back(word);
    } else {
      some_uppercase_words.push_back(word);
    }
  }

  std::cout << "\nThe words that are all lowercase are:\n";
  print_words(all_lowercase_words);
  std::cout << "\nThe words that have at least one uppercase letter are:\n";
  print_words(some_uppercase_words);
}

bool all_lowercase(std::string s) {
  for (std::string::const_iterator it = s.begin(); it < s.end(); ++it) {
    if (!islower(*it)) {
      return false;
    }
  }
  return true;
}

void print_words(std::vector<std::string> words) {
  for (std::vector<std::string>::const_iterator it = words.begin();
       it < words.end(); ++it) {
    std::cout << *it << '\n';
  }
}
