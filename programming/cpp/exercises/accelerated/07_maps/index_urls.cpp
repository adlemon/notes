// index_urls.cpp
// Read lines of input from the user. After reading all of the lines, print an
// index with all of the unique URLs in the input, and the line numbers on which
// they occurred.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<int> > Index;

bool is_url_char(char c);
std::string::const_iterator find_url_begin(
  const std::string::const_iterator& begin,
  const std::string::const_iterator& end
);
std::string::const_iterator find_url_end(
  const std::string::const_iterator& begin,
  const std::string::const_iterator& end
);
std::vector<std::string> find_urls(const std::string& s);
Index index_input(std::istream& in);
std::ostream& print(std::ostream& out, const Index& idx);

int main() {
  std::cout << "Enter the input to index:\n";
  Index idx = index_input(std::cin);

  std::cout << "\n\nThe index of URLs in the input is:\n";
  print(std::cout, idx);
}

bool is_url_char(char c) {
  static const std::string url_chars =  "~;/?:@=&$-_.+!*`(),";
  return isalnum(c) || std::find(
    url_chars.begin(),
    url_chars.end(),
    c
  ) != url_chars.end();
}

std::string::const_iterator find_url_begin(
  const std::string::const_iterator& b,
  const std::string::const_iterator& e
) {
  static const std::string url_sep = "://";

  std::string::const_iterator it = b;
  while ((it = std::search(it, e, url_sep.begin(), url_sep.end())) != e) {
    // Check for valid characters before and after the URL separator.
    if (it != b && is_url_char(it[-1]) && it + url_sep.size() != e
        && is_url_char(it[url_sep.size()])) {
      // Backtrack to the beginning of the URL.
      while (it != b && is_url_char(it[-1])) {
        --it;
      }
      return it;
    }

    it += url_sep.size();
  }

  return e;
}

std::string::const_iterator find_url_end(
  const std::string::const_iterator& b,
  const std::string::const_iterator& e
) {
  return std::find_if_not(b, e, is_url_char);
}

std::vector<std::string> find_urls(const std::string& s) {
  std::vector<std::string> urls;

  std::string::const_iterator it = s.begin();
  while ((it = find_url_begin(it, s.end())) != s.end()) {
    std::string::const_iterator jt = find_url_end(it, s.end());
    if (jt != it) {
      urls.push_back(std::string(it, jt));
    }
    it = jt;
  }

  return urls;
}

Index index_input(std::istream& in) {
  Index idx;

  int line_number = 0;
  std::string line;
  while (std::cout << "[" << line_number + 1 << "]: "
      && std::getline(in, line)) {
    ++line_number;
    std::vector<std::string> urls = find_urls(line);

    for (std::vector<std::string>::const_iterator it = urls.begin();
        it != urls.end(); ++it) {
      if (idx[*it].empty() || idx[*it][idx[*it].size() - 1] != line_number) {
        idx[*it].push_back(line_number);
      }
    }
  }

  return idx;
}

std::ostream& print(std::ostream& out, const Index& idx) {
  std::string::size_type max_key_length = 0;
  for (Index::const_iterator it = idx.begin(); it != idx.end(); ++it) {
    max_key_length = std::max(max_key_length, it->first.size());
  }

  for (Index::const_iterator it = idx.begin(); it != idx.end(); ++it) {
    out << it->first << std::string(max_key_length - it->first.size(), ' ')
        << ": ";
    for (std::vector<int>::const_iterator jt = it->second.begin();
        jt != it->second.end(); ++jt) {
      if (jt != it->second.begin()) {
        out << ", ";
      }

      out << *jt;
    }
    out << "\n";
  }

  return out;
}
