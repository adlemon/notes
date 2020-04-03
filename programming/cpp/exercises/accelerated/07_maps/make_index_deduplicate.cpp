// make_index_deduplicate.cpp
// Read lines from the user. Split each line that is read into words. For each
// unique word in the input, keep track of all of the unique lines on which the
// word occurred. After all of the input has been read, print out the unique
// words and the unique lines on which each word occurred.

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::vector<int> LineNumbers;
typedef std::string Word;
typedef std::map<Word, LineNumbers> Index;

std::vector<Word> split_words(const std::string &s);
Index index_input(std::istream &in, std::vector<Word> tokenize(
                                        const std::string &s) = split_words);
std::ostream &print(std::ostream &out, const Index &idx);

int main() {
  std::cout << "Enter the corpus to index:\n";
  Index idx = index_input(std::cin);

  std::cout << "\nThe unique words in the input and the unique lines on which\n"
            << "each word occurred are:\n";
  print(std::cout, idx);
}

std::vector<Word> split_words(const std::string &s) {
  std::vector<Word> words;

  std::string::const_iterator it = s.begin();
  while (it != s.end()) {
    while (it != s.end() && isspace(*it)) {
      ++it;
    }

    std::string::const_iterator jt = it;
    while (jt != s.end() && !isspace(*jt)) {
      ++jt;
    }

    if (jt != it) {
      words.push_back(std::string(it, jt));
    }
    it = jt;
  }

  return words;
}

Index index_input(std::istream &in,
                  std::vector<Word> tokenize(const std::string &s)) {
  Index idx;

  int line_number = 0;
  std::string line;
  while (std::getline(in, line)) {
    line_number++;

    std::vector<Word> tokens = tokenize(line);
    for (std::vector<Word>::const_iterator it = tokens.begin();
         it != tokens.end(); ++it) {
      LineNumbers &token_line_numbers = idx[*it];
      if (token_line_numbers.empty() ||
          token_line_numbers[token_line_numbers.size() - 1] != line_number) {
        token_line_numbers.push_back(line_number);
      }
    }
  }

  return idx;
}

std::ostream &print(std::ostream &out, const Index &idx) {
  for (Index::const_iterator it = idx.begin(); it != idx.end(); ++it) {
    out << it->first << ": ";
    for (LineNumbers::const_iterator jt = it->second.begin();
         jt != it->second.end(); ++jt) {
      if (jt != it->second.begin()) {
        out << ", ";
      }
      out << *jt;
    }
    out << '\n';
  }
  return out;
}
