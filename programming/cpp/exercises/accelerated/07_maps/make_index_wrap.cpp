// make_index_wrap.cpp
// Read lines from the user. Split each line that is read into words. For each
// unique word in the input, keep track of all of the unique lines on which the
// word occurred. After all of the input has been read, print out the unique
// words and the unique lines on which each word occurred. We print at most 3
// line numbers on each line of the index, and start a new line every 3 line
// numbers.

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const int NUM_LINE_NUMBERS_PER_INDEX_LINE = 3;

typedef std::map<std::string, std::vector<int>> IndexType;

std::vector<std::string> split_words(const std::string &s);
IndexType index_input(
    std::istream &in,
    std::vector<std::string> tokenize(const std::string &s) = split_words);
std::ostream &print(std::ostream &out, const IndexType &idx);

int main() {
  std::cout << "Enter the corpus:\n";
  IndexType idx = index_input(std::cin);

  std::cout << "\nThe index is:\n";
  print(std::cout, idx);
}

std::vector<std::string> split_words(const std::string &s) {
  std::vector<std::string> words;

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

IndexType index_input(std::istream &in,
                      std::vector<std::string> tokenize(const std::string &s)) {
  IndexType idx;

  int line_number = 0;
  std::string line;
  while (std::getline(in, line)) {
    line_number++;

    std::vector<std::string> tokens = tokenize(line);
    for (std::vector<std::string>::const_iterator it = tokens.begin();
         it != tokens.end(); ++it) {
      std::vector<int> &token_line_numbers = idx[*it];
      if (token_line_numbers.empty() ||
          token_line_numbers[token_line_numbers.size() - 1] != line_number) {
        token_line_numbers.push_back(line_number);
      }
    }
  }

  return idx;
}

std::ostream &print(std::ostream &out, const IndexType &idx) {
  for (IndexType::const_iterator it = idx.begin(); it != idx.end(); ++it) {
    out << it->first << ": ";

    int line_number_count = 0;
    for (std::vector<int>::const_iterator jt = it->second.begin();
         jt != it->second.end(); ++jt) {
      if (jt != it->second.begin()) {
        if ((line_number_count % 3) == 0) {
          out << ",\n" << std::string(it->first.size() + 2, ' ');
        } else {
          out << ", ";
        }
      }
      out << *jt;
      line_number_count++;
    }
    out << '\n';
  }

  return out;
}
