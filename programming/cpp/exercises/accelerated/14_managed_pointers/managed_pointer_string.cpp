// managed_pointer_string.cpp
// Implement and test a string class using the ManagedPointer class.

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>

#include "../11_abstract_data_types/simple_vector.cpp"
#include "managed_pointer.cpp"

class ManagedPointerString {
  friend std::istream &operator>>(std::istream &is, ManagedPointerString &s);

public:
  ManagedPointerString() : data_(new SimpleVector<char>) {}
  ManagedPointerString(const char *s) : data_(new SimpleVector<char>) {
    std::copy(s, s + std::strlen(s), std::back_inserter(*data_));
  }
  typedef SimpleVector<char>::size_type size_type;
  ManagedPointerString(size_type n, char c)
      : data_(new SimpleVector<char>(n, c)) {}
  template <class In>
  ManagedPointerString(In i, In j) : data_(new SimpleVector<char>) {
    std::copy(i, j, std::back_inserter(*data_));
  }

  size_type size() const { return data_->size(); }
  char &operator[](size_type i) {
    data_.make_unique();
    return (*data_)[i];
  }
  const char &operator[](size_type i) const { return (*data_)[i]; }
  ManagedPointerString &operator+=(const ManagedPointerString &s) {
    data_.make_unique();
    std::copy(s.data_->begin(), s.data_->end(), std::back_inserter(*data_));
    return *this;
  }

private:
  ManagedPointer<SimpleVector<char>> data_;
};

std::ostream &operator<<(std::ostream &os, const ManagedPointerString &s) {
  for (ManagedPointerString::size_type i = 0; i != s.size(); ++i) {
    os << s[i];
  }
  return os;
}

ManagedPointerString operator+(const ManagedPointerString &s1,
                               const ManagedPointerString &s2) {
  ManagedPointerString s = s1;
  s += s2;
  return s;
}

template <>
inline SimpleVector<char> *clone(const SimpleVector<char> *pointer_) {
  return new SimpleVector<char>(*pointer_);
}

SimpleVector<ManagedPointerString> string_split(const ManagedPointerString &s) {
  SimpleVector<ManagedPointerString> tokens;

  ManagedPointerString::size_type i = 0;
  while (i < s.size()) {
    while (i < s.size() && isspace(s[i])) {
      ++i;
    }

    ManagedPointerString::size_type j = i;
    while (j < s.size() && !isspace(s[j])) {
      ++j;
    }

    if (i != j) {
      tokens.push_back(ManagedPointerString(&s[i], &s[j]));
    }
    i = j;
  }

  return tokens;
}

int main() {
  const std::string prompt = "Enter a line of text (or end-of-file to quit): ";
  std::string line;

  std::cout << prompt;
  while (std::getline(std::cin, line)) {
    ManagedPointerString s(line.begin(), line.end());
    SimpleVector<ManagedPointerString> tokens = string_split(s);

    for (SimpleVector<ManagedPointerString>::const_iterator it = tokens.begin();
         it != tokens.end(); ++it) {
      std::cout << "token: " << *it << "\n";
    }

    std::cout << "\n" << prompt;
  }
}
