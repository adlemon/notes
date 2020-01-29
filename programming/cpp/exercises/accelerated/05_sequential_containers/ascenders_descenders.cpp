// ascenders_descenders.cpp
// Read words from the user. After reading the words, print all words that have
// either an ascender ('b', 'd', 'f', h', 'k', or 'l') or descender ('g', 'j',
// 'p', 'q', or 'y'), and the longest such word.

#include <iostream>
#include <string>
#include <vector>

bool has_char(const std::string& s, char c);
bool intersect(const std::string& s1, const std::string& s2);
bool has_ascender(const std::string& s);
bool has_descender(const std::string& s);
bool has_ascender_or_descender(const std::string& s);

int main() {
  std::string word;
  std::string longest;
  std::vector<std::string> words;

  std::cout << "Enter the words followed by an end-of-file:\n";
  while (std::cin >> word) {
    if (has_ascender_or_descender(word)) {
      words.push_back(word);
      if (word.size() > longest.size()) {
        longest = word;
      }
    }
  }

  if (words.empty()) {
    std::cout << "\nThere were no words with an ascender or descender.\n";
  } else {
    std::cout << "\nThe words with an ascender or descender are:\n";
    for (std::vector<std::string>::const_iterator it = words.begin();
        it != words.end(); ++it) {
      std::cout << *it << '\n';
    }

    std::cout << "\nThe longest word with an ascender or descender is: "
              << longest << '\n';
  }
}

// either an ascender ('b', 'd', 'f', h', 'k', or 'l') or descender ('g', 'j',
// 'p', 'q', or 'y'), and the longest such word.
bool has_char(const std::string& s, char c) {
  for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
    if (*it == c) {
      return true;
    }
  }
  return false;
}

bool intersect(const std::string& s1, const std::string& s2) {
  for (std::string::const_iterator it = s2.begin(); it != s2.end(); ++it) {
    if (has_char(s1, *it)) {
      return true;
    }
  }
  return false;
}

bool has_ascender(const std::string& s) {
  return intersect(s, "bdfhkl");
}

bool has_descender(const std::string& s) {
  return intersect(s, "gjpqy");
}

bool has_ascender_or_descender(const std::string& s) {
  return has_ascender(s) || has_descender(s);
}
