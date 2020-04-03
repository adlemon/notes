// split.cpp
// Write a template function to split a string into words, and store the
// results in a container.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

template <class IteratorType>
void split(const std::string &s, IteratorType out) {
  std::string::const_iterator it = s.begin();
  while (it != s.end()) {
    it = std::find_if_not(it, s.end(), isspace);
    if (it != s.end()) {
      std::string::const_iterator jt = std::find_if(it, s.end(), isspace);
      *out = std::string(it, jt);
      ++out;
      it = jt;
    }
  }
}

int main() {
  std::string s;
  std::cout << "Enter a string: ";
  std::getline(std::cin, s);

  std::vector<std::string> v;
  split(s, std::back_inserter(v));
  std::cout << "\nThe vector of words is: ";
  std::copy(v.begin(), v.end(),
            std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << "\n";

  std::list<std::string> lst;
  split(s, std::back_inserter(lst));
  std::cout << "\nThe list of words is: ";
  std::copy(lst.begin(), lst.end(),
            std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << "\n";
}
