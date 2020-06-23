// read_integer.cpp
// Read integers from the standard input.

#include <iostream>
#include <sstream>
#include <string>

void skip_to_int(std::istream &is);
int get_int(std::istream &is, const std::string &prompt,
            const std::string &range_error_msg);
int get_int(std::istream &is, int min, int max, const std::string &prompt,
            const std::string &type_error_msg,
            const std::string &range_error_msg);

constexpr int num_to_read = 5;
constexpr int min_to_read = 1;
constexpr int max_to_read = 10;
const std::string prompt = "Enter an integer";
const std::string type_error_msg = "That is not an integer.";
const std::string range_error_msg = "That integer is not the desired range.";

int main() {
  for (int i = 0; i < num_to_read; ++i) {
    int x = get_int(std::cin, min_to_read, max_to_read, prompt, type_error_msg,
                    range_error_msg);
    std::cout << "Read integer: " << x << "\n\n";
  }
}

void skip_to_int(std::istream &is) {
  if (is.fail()) {
    is.clear();
    for (char c; is >> c;) {
      if (isdigit(c) || c == '-') {
        is.unget();
        return;
      }
    }
  }

  throw std::runtime_error("Failed to read integer.");
}

int get_int(std::istream &is, const std::string &prompt,
            const std::string &type_error_msg) {
  int i;
  std::cout << prompt;
  while (true) {
    if (is >> i) {
      return i;
    }
    std::cout << type_error_msg << "\n\n";
    std::cout << prompt;
    skip_to_int(is);
  }
}

int get_int(std::istream &is, int min, int max, const std::string &prompt,
            const std::string &type_error_msg,
            const std::string &range_error_msg) {
  std::stringstream ss;
  ss << prompt << " between " << min << " and " << max << ": ";
  while (true) {
    int i = get_int(is, ss.str(), type_error_msg);
    if (min <= i && i <= max) {
      return i;
    }
    std::cout << range_error_msg << "\n\n";
  }
}
