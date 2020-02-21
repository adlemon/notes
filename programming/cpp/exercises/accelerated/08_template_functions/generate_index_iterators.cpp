// generate_index_iterators.cpp
// Read input from the user and generate index that shows the line numbers on
// which each word in the input appeared.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::list<int> > Index;

std::list<std::string> tokenize(const std::string& s);
Index index_input(std::istream& in);

template <class T>
void write_index(const Index& idx, T out);

int main() {
  Index idx = index_input(std::cin);

  std::cout << "\n\nIndex written directly to the standard output:\n";
  write_index(idx, std::ostream_iterator<std::string>(std::cout));

  std::list<std::string> idx_strings;
  write_index(idx, std::back_inserter(idx_strings));

  std::cout << "\nIndex written to a list of strings:\n";
  std::copy(
    idx_strings.begin(),
    idx_strings.end(),
    std::ostream_iterator<std::string>(std::cout)
  );
}

std::list<std::string> tokenize(const std::string& s) {
  std::list<std::string> words;

  std::string::const_iterator it = s.begin();
  while (it != s.end()) {
    it = std::find_if_not(it, s.end(), isspace);
    std::string::const_iterator jt = std::find_if(it, s.end(), isspace);
    words.push_back(std::string(it, jt));
    it = jt;
  }

  return words;
}

Index index_input(std::istream& in) {
  Index idx;

  int line_number = 0;
  std::string line;
  while (std::cout << "[" << line_number + 1 << "] "
      && std::getline(in, line)) {
    ++line_number;

    std::list<std::string> words = tokenize(line);
    for (std::list<std::string>::const_iterator it = words.begin();
        it != words.end(); ++it) {
      if (idx[*it].empty() || idx[*it].back() != line_number) {
        idx[*it].push_back(line_number);
      }
    }
  }

  return idx;
}

template <class T>
void write_index(const Index& idx, T out) {
  for (Index::const_iterator it = idx.begin(); it != idx.end(); ++it) {
    *out = it->first;
    *out = ": ";
    for (std::list<int>::const_iterator jt = it->second.begin();
        jt != it->second.end(); ++jt) {
      if (jt != it->second.begin()) {
        *out = ", ";
      }
      *out = std::to_string(*jt);
    }
    *out = "\n";
  }
}

