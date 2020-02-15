// make_index.cpp
// Read lines from the user and build an index from words to line numbers.

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<int> > IndexType;

std::vector<std::string> split_words(const std::string& s);

IndexType build_index(
  std::istream& in,
  std::vector<std::string> tokenize(const std::string& line) = split_words
);

std::ostream& print(std::ostream& out, const IndexType& idx);

int main() {
  std::cout << "Enter the corpus:\n";
  IndexType idx = build_index(std::cin);

  std::cout << "\nThe indexed corpus is:\n";
  print(std::cout, idx);
}

std::vector<std::string> split_words(const std::string& s) {
  std::vector<std::string> words;

  std::string::const_iterator it = s.begin();
  while (it != s.end()) {
    while (it != s.end() && std::isspace(*it)) {
      ++it;
    }

    std::string::const_iterator jt = it;
    while (jt != s.end() && !std::isspace(*jt)) {
      ++jt;
    }

    if (it != jt) {
      words.push_back(std::string(it, jt));
    }
    it = jt;
  }

  return words;
}

IndexType build_index(
  std::istream& in,
  std::vector<std::string> tokenize(const std::string& line)
) {
  IndexType idx;

  int line_number = 0;
  std::string line;
  while (std::getline(in, line)) {
    ++line_number;

    std::vector<std::string> tokens = tokenize(line);
    for (std::vector<std::string>::const_iterator token = tokens.begin();
        token != tokens.end(); ++token) {
      idx[*token].push_back(line_number);
    }
  }

  return idx;
}

std::ostream& print(std::ostream& out, const IndexType& idx) {
  for (IndexType::const_iterator it = idx.begin(); it != idx.end(); ++it) {
    out << it->first << ": ";
    for (std::vector<int>::const_iterator jt = it->second.begin();
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
