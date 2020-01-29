// print_palindromes.cpp
// Read words from the user; after reading all of the words, print all of the
// palindromes, and the longest palindrome.

#include <iostream>
#include <string>
#include <vector>

bool is_palindrome(std::string s);

int main() {
  std::vector<std::string> words;

  std::string word;
  std::cout << "Enter the words followed by an end-of-file:\n";
  while (std::cin >> word) {
    words.push_back(word);
  }

  std::vector<std::string> palindromes;
  for (std::vector<std::string>::const_iterator it = words.begin();
      it < words.end(); ++it) {
    if (is_palindrome(*it)) {
      palindromes.push_back(*it);
    }
  }

  if (palindromes.empty()) {
    std::cout << "\nThe input did not contain any palindromes.\n";
    return 0;
  }

  std::string longest_palindrome;
  std::cout << "\nThe palindromes are:\n";
  for (std::vector<std::string>::const_iterator it = palindromes.begin();
      it < palindromes.end(); ++it) {
    std::cout << *it << '\n';
    if (it->size() > longest_palindrome.size()) {
      longest_palindrome = *it;
    }
  }
  
  std::cout << "\nThe longest palindrome is: " << longest_palindrome << "\n";
}

bool is_palindrome(std::string s) {
  for (std::string::const_iterator left = s.begin(), right = s.end() - 1;
      left < right; ++left, --right) {
    if (*left != *right) {
      return false;
    }
  }
  return true;
}
