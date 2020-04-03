// generate_index_line_vs_lines.cpp
// Read lines from the user. For each unique word read from the user, print the
// unique lines on which the word occurred.

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<int>> Index;

std::vector<std::string> split_string(const std::string s);
Index index_input(std::istream &in);
std::ostream &print(std::ostream &out, const Index &idx);

int main() {
  std::cout << "Enter the corpus to index:\n";
  Index idx = index_input(std::cin);

  std::cout << "\n\nThe index of the corpus is:\n";
  print(std::cout, idx);
}

std::vector<std::string> split_string(const std::string s) {
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

    if (it != jt) {
      words.push_back(std::string(it, jt));
    }

    it = jt;
  }

  return words;
}

Index index_input(std::istream &in) {
  Index idx;

  int line_number = 0;
  std::string line;
  while (std::cout << "(" << line_number + 1 << "): " &&
         std::getline(in, line)) {
    ++line_number;
    const std::vector<std::string> words = split_string(line);

    for (std::vector<std::string>::const_iterator it = words.begin();
         it != words.end(); ++it) {
      if (idx[*it].empty() || idx[*it][idx[*it].size() - 1] != line_number) {
        idx[*it].push_back(line_number);
      }
    }
  }

  return idx;
}

std::ostream &print(std::ostream &out, const Index &idx) {
  for (Index::const_iterator it = idx.begin(); it != idx.end(); ++it) {
    const std::string &word = it->first;
    const std::vector<int> &line_numbers = it->second;

    out << "\"" << word << "\" appears on line"
        << ((line_numbers.size() > 1) ? "s" : "") << ": ";
    for (std::vector<int>::const_iterator jt = line_numbers.begin();
         jt != line_numbers.end(); ++jt) {
      if (jt != line_numbers.begin()) {
        out << ", ";
      }
      out << *jt;
    }
    out << "\n";
  }

  return out;
}
