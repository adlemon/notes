// copy_cstring.cpp
// Copy a pointer to a null-terminated sequence of characters.

#include <algorithm>
#include <cstring>
#include <iostream>

char *copy(const char *s);

int main() {
  const char s[] = {'a', 'b', 'c', '\0'};

  std::cout << "The original string is: " << s << "\n";

  char *c = copy(s);
  std::cout << "The copied string is: " << c << "\n";

  delete[] c;
}

char *copy(const char *s) {
  size_t n_chars = strlen(s);
  char *c = new char[n_chars + 1];

  std::copy(s, s + n_chars + 1, c);
  return c;
}
