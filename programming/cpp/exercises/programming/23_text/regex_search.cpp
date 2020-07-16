// regex_search.cpp
// Demonstrates the use of regex searches.

#include <iostream>
#include <regex>
#include <string>

struct RegexExample {
  std::string regex_pattern;
  std::vector<std::string> test_strings;
  // RegexExample(const std::string &regex_pattern,
  // const std::vector<std::string> &test_strings)
  //: regex_pattern{regex_pattern}, test_strings{test_strings} {}
};

std::ostream &operator<<(std::ostream &os, const RegexExample &regex_example) {
  os << "regular expression: " << regex_example.regex_pattern << "\n";
  std::regex rgx{regex_example.regex_pattern};
  for (const std::string &test_string : regex_example.test_strings) {
    os << "--> test string: " << test_string << "\n";
    std::smatch regex_matches;
    if (!std::regex_search(test_string, regex_matches, rgx)) {
      os << std::string(4, ' ') << "--> no matches\n";
      continue;
    }
    for (size_t i = 0; i < regex_matches.size(); ++i) {
      os << std::string(4, ' ') << "--> match[" << i
         << "]: " << regex_matches[i] << "\n";
    }
  }
  return os;
}

int main() {
  // The wildcard character.
  std::cout << RegexExample{R"(a.b)", {"axb", "ayb", "ab", "abc"}};

  // The * character.
  std::cout << "\n"
            << RegexExample{R"(ax*b)", {"ab", "axb", "axxb", "axxxb", "ayb"}};

  // The + character.
  std::cout << "\n"
            << RegexExample{R"(ax+b)", {"ab", "axb", "axxb", "axxxb", "ayb"}};

  // The ? character.
  std::cout << "\n"
            << RegexExample{R"(ax?b)", {"ab", "axb", "axxb", "axxxb", "ayb"}};

  // The {n}, {n,}, and {n,m} repeat patterns.
  std::cout
      << "\n"
      << RegexExample{R"(ax{2}b)", {"ab", "axb", "axxb", "axxxb", "axxxxb"}}
      << RegexExample{R"(ax{2,}b)", {"ab", "axb", "axxb", "axxxb", "axxxxb"}}
      << RegexExample{R"(ax{2,3}b)", {"ab", "axb", "axxb", "axxxb", "axxxxb"}};

  // Character class \d == [[:digit:]].
  std::cout << "\n"
            << RegexExample{R"(\d)", {"a", "1"}}
            << RegexExample{R"([[:digit:]])", {"a", "1"}};
  // Character class \D.
  std::cout << RegexExample{R"(\D)", {"a", "1"}};

  // Character class [[:lower:]].
  std::cout << "\n" << RegexExample{R"([[:lower:]])", {"a", "A", "1"}};

  // Character class \s == [[:space:]].
  std::cout << "\n"
            << RegexExample{R"(a\sb)", {"ab", "axb", "a b"}} << "\n"
            << RegexExample{R"(a[[:space:]]b)", {"ab", "axb", "a b"}};
  // Character class \S.
  std::cout << RegexExample{R"(a\Sb)", {"ab", "axb", "a1b", "a b"}};

  // Character class [[:upper:]].
  std::cout << "\n" << RegexExample{R"([[:upper:]])", {"a", "A", "1"}};

  // Character class \w == [[:alnum]].
  std::cout << "\n" << RegexExample{R"(a\wb)", {"ab", "axb", "a1b", "a b"}};
  // Character class \W.
  std::cout << RegexExample{R"(a\Wb)", {"ab", "axb", "a1b", "a b"}};

  // Groups.
  std::cout << "\n" << RegexExample{R"((a*)(b))", {"a", "b", "ab", "aab"}};

  // Alternation.
  std::cout << "\n"
            << RegexExample{R"((a|b)(x|y))", {"ab", "ax", "ay", "bx", "by"}};

  // Character sets and ranges.
  std::cout << "\n"
            << RegexExample{R"([ab][xy])", {"ab", "ax", "ay", "bx", "by"}}
            << RegexExample{R"([a-c][x-z])", {"ac", "az", "by", "cx"}}
            << RegexExample{R"([^ax])", {"a", "b", "x", "y"}};
}
