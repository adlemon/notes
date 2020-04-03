// simple_string.cpp
// Simple implementation of a string class.

#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class SimpleString {
public:
  typedef std::vector<char>::size_type size_type;
  typedef std::vector<char>::iterator iterator;
  typedef std::vector<char>::const_iterator const_iterator;

  SimpleString() : raw_str_(nullptr), raw_chars_(nullptr) {}
  SimpleString(size_type n, char c)
      : chars_(n, c), raw_str_(nullptr), raw_chars_(nullptr) {}
  SimpleString(const char *c) : raw_str_(nullptr), raw_chars_(nullptr) {
    std::copy(c, c + std::strlen(c), std::back_inserter(chars_));
  }
  template <class In>
  SimpleString(In begin, In end)
      : chars_(begin, end), raw_str_(nullptr), raw_chars_(nullptr) {}
  ~SimpleString() {
    if (raw_str_) {
      delete[] raw_str_;
    }
    if (raw_chars_) {
      delete[] raw_chars_;
    }
  }

  size_type size() const { return chars_.size(); }
  operator bool() const { return size() != 0; }
  char &operator[](size_type i) { return chars_[i]; }
  const char &operator[](size_type i) const { return chars_[i]; }

  iterator begin() { return chars_.begin(); }
  const_iterator begin() const { return chars_.begin(); }
  iterator end() { return chars_.end(); }
  const_iterator end() const { return chars_.end(); }

  const char *c_str() {
    if (raw_str_) {
      delete[] raw_str_;
    }

    raw_str_ = new char[chars_.size() + 1];
    for (std::vector<char>::size_type i = 0; i < chars_.size(); ++i) {
      raw_str_[i] = chars_[i];
    }
    raw_str_[chars_.size()] = '\0';

    return raw_str_;
  }

  const char *data() {
    if (raw_chars_) {
      delete raw_chars_;
    }

    raw_chars_ = new char[chars_.size()];
    for (std::vector<char>::size_type i = 0; i < chars_.size(); ++i) {
      raw_chars_[i] = chars_[i];
    }

    return raw_chars_;
  }

  void copy(char *p, size_type n) const {
    for (size_type i = 0; i < n && i < chars_.size(); ++i) {
      p[i] = chars_[i];
    }
  }

  SimpleString &operator+=(const SimpleString &s) {
    std::copy(s.chars_.begin(), s.chars_.end(), std::back_inserter(chars_));
    return *this;
  }

  friend std::istream &operator>>(std::istream &is, SimpleString &s);
  friend std::istream &getline(std::istream &is, SimpleString &s);
  friend SimpleString operator+(const SimpleString &s, const char *p);
  friend SimpleString operator+(const char *p, const SimpleString &s);

private:
  std::vector<char> chars_;
  char *raw_str_;
  char *raw_chars_;
};

std::istream &operator>>(std::istream &is, SimpleString &s) {
  s.chars_.clear();

  char c;
  while (is.get(c) && isspace(c))
    ;

  if (is) {
    do {
      s.chars_.push_back(c);
    } while (is.get(c) && !isspace(c));

    if (is) {
      is.unget();
    }
  }

  return is;
}

std::istream &getline(std::istream &is, SimpleString &s) {
  s.chars_.clear();

  if (is) {
    char c;
    while (is.get(c) && c != '\n') {
      s.chars_.push_back(c);
    }
  }

  return is;
}

std::ostream &operator<<(std::ostream &os, const SimpleString &s) {
  std::copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout));
  return os;
}

SimpleString operator+(const SimpleString &s1, const SimpleString &s2) {
  SimpleString s = s1;
  s += s2;
  return s;
}

SimpleString operator+(const SimpleString &s, const char *p) {
  int length_p = strlen(p);

  SimpleString c(s);
  c.chars_.reserve(s.size() + length_p);
  for (int i = 0; i < length_p; ++i) {
    c.chars_.push_back(p[i]);
  }

  return c;
}

SimpleString operator+(const char *p, const SimpleString &s) {
  SimpleString c(p);
  c.chars_.reserve(strlen(p) + s.size());
  for (SimpleString::size_type i = 0; i < s.size(); ++i) {
    c.chars_.push_back(s[i]);
  }
  return c;
}

int strcmp(const SimpleString &s1, const SimpleString &s2) {
  char *c_str_1 = new char[s1.size() + 1];
  s1.copy(c_str_1, s1.size());
  c_str_1[s1.size()] = '\0';

  char *c_str_2 = new char[s2.size() + 1];
  s2.copy(c_str_2, s2.size());
  c_str_2[s2.size()] = '\0';

  int result = std::strcmp(c_str_1, c_str_2);

  delete[] c_str_1;
  delete[] c_str_2;

  return result;
}

bool operator<(const SimpleString &s1, const SimpleString &s2) {
  return strcmp(s1, s2) < 0;
}

bool operator<=(const SimpleString &s1, const SimpleString &s2) {
  return strcmp(s1, s2) <= 0;
}

bool operator>(const SimpleString &s1, const SimpleString &s2) {
  return strcmp(s1, s2) > 0;
}

bool operator>=(const SimpleString &s1, const SimpleString &s2) {
  return strcmp(s1, s2) >= 0;
}

bool operator==(const SimpleString &s1, const SimpleString &s2) {
  if (s1.size() != s2.size()) {
    return false;
  }

  for (SimpleString::size_type i = 0; i < s1.size(); ++i) {
    if (s1[i] != s2[i]) {
      return false;
    }
  }

  return true;
}

bool operator!=(const SimpleString &s1, const SimpleString &s2) {
  return !(s1 == s2);
}

int main() {
  SimpleString s1, s2;

  std::cout << "Enter the first string: ";
  std::cin >> s1;
  std::cout << "Enter the second string: ";
  std::cin >> s2;

  SimpleString s = s1 + s2;
  std::cout << "The concatenation of the two strings is: " << s << "\n";

  std::vector<char> v;
  for (char c = 'a'; c <= 'z'; ++c) {
    v.push_back(c);
  }
  SimpleString alphabet(v.begin(), v.end());
  std::cout << "The lowercase alphabet is: " << alphabet.c_str() << "\n";

  char *raw_str = new char[10];
  alphabet.copy(raw_str, 9);
  raw_str[9] = '\0';
  std::cout << "The alphabet begins: " << raw_str << "\n";
  delete[] raw_str;

  {
    SimpleString s1("Hello"), s2("World");
    std::cout << s1 + ", World!\n";
    std::cout << "Hello, " + s2 << "!\n";
  }

  {
    SimpleString empty_string(""), nonempty_string("Hello, World!");

    if (empty_string) {
      std::cout << "The empty string is true in conditions.\n";
    } else {
      std::cout << "The empty string is false in conditions.\n";
    }

    if (nonempty_string) {
      std::cout << "A nonempty string is true in conditions.\n";
    } else {
      std::cout << "A nonempty string is false in conditions.\n";
    }
  }

  {
    SimpleString s = "0123456789";
    std::cout << "The Arabic numerals are: ";
    for (SimpleString::iterator it = s.begin(); it != s.end(); ++it) {
      if (it != s.begin()) {
        std::cout << ", ";
      }
      std::cout << *it;
    }
    std::cout << "\n";
  }

  {
    SimpleString s;
    std::cout << "Enter a line of text: ";
    getline(std::cin, s);
    getline(std::cin, s);
    std::cout << "You entered the following line of text: " << s << "\n";
  }
}
