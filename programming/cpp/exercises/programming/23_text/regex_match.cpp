// regex_match.cpp
// Demonstrates the difference between a regex search and regex match.

#include <iostream>
#include <regex>
#include <string>

int main() {
  std::string test_string{"abcd"};

  std::smatch regex_matches;
  for (const std::string &regex_pattern : {"abcd", "bc"}) {
    if (std::regex_search(test_string, regex_matches,
                          std::regex{regex_pattern})) {
      std::cout << "regex_search for " << regex_pattern << " on " << test_string
                << " succeeds.\n";
    } else {
      std::cout << "regex_search for " << regex_pattern << " on " << test_string
                << " fails.\n";
    }

    if (std::regex_match(test_string, regex_matches,
                         std::regex{regex_pattern})) {
      std::cout << "regex_match for " << regex_pattern << " on " << test_string
                << " succeeds.\n";
    } else {
      std::cout << "regex_match for " << regex_pattern << " on " << test_string
                << " fails.\n";
    }
  }
}
