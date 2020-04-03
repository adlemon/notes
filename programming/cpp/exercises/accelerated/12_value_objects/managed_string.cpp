// managed_string.cpp
// Simple implementation of a string class that manages storage for the
// underling character array.

#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

class ManagedString {
public:
  typedef size_t size_type;

  ManagedString() : size_(0) {
    chars_ = new char[size_ + 1];
    chars_[size_] = '\0';
  }
  ManagedString(const ManagedString &other) : size_(other.size_) {
    chars_ = new char[size_ + 1];
    for (size_type i = 0; i < size_; ++i) {
      chars_[i] = other.chars_[i];
    }
    chars_[size_] = '\0';
  }
  ManagedString(size_type n, char c) {
    size_ = n;
    chars_ = new char[n + 1];
    for (size_type i = 0; i < size_; ++i) {
      chars_[i] = c;
    }
    chars_[size_] = '\0';
  }
  ManagedString(const char *c) {
    size_ = std::strlen(c);
    chars_ = new char[size_ + 1];
    for (size_type i = 0; i < size_; ++i) {
      chars_[i] = c[i];
    }
    chars_[size_] = '\0';
  }
  template <class In> ManagedString(In begin, In end) {
    size_ = 0;
    for (In it = begin; it != end; ++it, ++size_)
      ;

    size_type i = 0;
    chars_ = new char[size_ + 1];
    for (In it = begin; it != end; ++it) {
      chars_[i] = *it;
    }
    chars_[size_] = '\0';
  }
  ~ManagedString() { delete[] chars_; }

  size_type size() const { return size_; }
  char &operator[](size_type i) { return chars_[i]; }
  const char &operator[](size_type i) const { return chars_[i]; }

  ManagedString &operator+=(const ManagedString &s) {
    size_type old_size = size_;
    char *old_chars = chars_;

    size_ = old_size + s.size_;
    chars_ = new char[size_ + 1];
    for (size_type i = 0; i < old_size; ++i) {
      chars_[i] = old_chars[i];
    }
    for (size_type i = 0; i < s.size_; ++i) {
      chars_[old_size + i] = s.chars_[i];
    }
    chars_[size_] = '\0';

    delete[] old_chars;

    return *this;
  }

  friend std::istream &operator>>(std::istream &is, ManagedString &s);

private:
  size_type size_;
  char *chars_;
};

std::ostream &operator<<(std::ostream &os, ManagedString &s) {
  for (ManagedString::size_type i = 0; i < s.size(); ++i) {
    os << s[i];
  }
  return os;
}

std::istream &operator>>(std::istream &is, ManagedString &s) {
  s.size_ = 0;
  delete[] s.chars_;
  s.chars_ = new char[1];

  char c;
  while (is.get(c) && isspace(c))
    ;

  if (is) {
    ManagedString::size_type capacity = 0;
    do {
      if (s.size_ >= capacity) {
        capacity = (capacity > 0) ? (2 * capacity) : 1;
        char *old_chars = s.chars_;
        s.chars_ = new char[capacity + 1];
        for (ManagedString::size_type i = 0; i < s.size_; ++i) {
          s.chars_[i] = old_chars[i];
        }
        delete[] old_chars;
      }
      s.chars_[s.size_] = c;
      ++s.size_;
    } while (is.get(c) && !isspace(c));
  }
  s.chars_[s.size_] = '\0';

  return is;
}

ManagedString operator+(const ManagedString &s1, const ManagedString &s2) {
  ManagedString s = s1;
  s += s2;
  return s;
}

int main() {
  ManagedString s1, s2;

  std::cout << "Enter the first string: ";
  std::cin >> s1;
  std::cout << "Enter the second string: ";
  std::cin >> s2;

  ManagedString s = s1 + s2;
  std::cout << "The concatenation of the two strings is: " << s << "\n";

  ManagedString alphabet;
  for (char c = 'a'; c <= 'z'; ++c) {
    alphabet += ManagedString(1, c);
  }
  std::cout << "The lowercase alphabet is: " << alphabet << "\n";
}
