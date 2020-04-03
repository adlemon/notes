// find_urls.cpp
// Read text from the user and extract all of the URLs.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

bool is_url_char(char c);
std::string::const_iterator
find_url_begin(const std::string::const_iterator &b,
               const std::string::const_iterator &e);
std::string::const_iterator find_url_end(const std::string::const_iterator &b,
                                         const std::string::const_iterator &e);
std::vector<std::string> find_urls(const std::string &s);
void print(std::vector<std::string>::const_iterator b,
           const std::vector<std::string>::const_iterator &e);

int main() {
  std::string s;
  std::cout << "Enter the text followed by a newline: ";
  std::getline(std::cin, s);

  std::vector<std::string> urls = find_urls(s);
  std::cout << "\nThe URLs in the text are:\n";
  print(urls.begin(), urls.end());
}

bool is_url_char(char c) {
  static const std::string url_characters = "~;/?:@=&$-_.+!*`(),";
  return isalnum(c) ||
         std::find(url_characters.begin(), url_characters.end(), c) !=
             url_characters.end();
}

std::string::const_iterator
find_url_begin(const std::string::const_iterator &b,
               const std::string::const_iterator &e) {
  static const std::string url_sep = "://";

  std::string::const_iterator it = b;
  while ((it = std::search(it, e, url_sep.begin(), url_sep.end())) != e) {
    if (it != b && it + url_sep.size() != e) {
      // Backtrack from the URL separator to the beginning of the URL.
      std::string::const_iterator url_begin = it;
      while (url_begin != b && std::isalpha(url_begin[-1])) {
        --url_begin;
      }

      // Make sure that there is at least one URL character before and after the
      // URL separator.
      if (url_begin != it && is_url_char(it[url_sep.size()])) {
        return url_begin;
      }
    }

    it += url_sep.size();
  }
  return e;
}

std::string::const_iterator find_url_end(const std::string::const_iterator &b,
                                         const std::string::const_iterator &e) {
  return std::find_if_not(b, e, is_url_char);
}

std::vector<std::string> find_urls(const std::string &s) {
  std::vector<std::string> urls;

  std::string::const_iterator cursor = s.begin(), string_end = s.end();
  while (cursor != string_end) {
    cursor = find_url_begin(cursor, string_end);
    if (cursor != string_end) {
      std::string::const_iterator url_end = find_url_end(cursor, string_end);
      urls.push_back(std::string(cursor, url_end));
      cursor = url_end;
    }
  }

  return urls;
}

void print(std::vector<std::string>::const_iterator b,
           const std::vector<std::string>::const_iterator &e) {
  while (b != e) {
    std::cout << *b << '\n';
    ++b;
  }
}
