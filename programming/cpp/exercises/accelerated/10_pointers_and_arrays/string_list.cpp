// string_list.cpp
// Implement a class to hold lists of strings.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

class StringListNode {
public:
  StringListNode() : s_(""), prev_(nullptr), next_(nullptr) {}
  StringListNode(const std::string &s)
      : s_(s), prev_(nullptr), next_(nullptr) {}
  const std::string &s() { return s_; }

private:
  std::string s_;
  StringListNode *prev_, *next_;
  friend class StringList;
  friend class StringListIterator;
};

class StringListIterator {
public:
  StringListIterator(StringListNode *cursor) : cursor_(cursor) {}
  bool operator==(const StringListIterator &other) const {
    return cursor_ == other.cursor_;
  }
  bool operator!=(const StringListIterator &other) const {
    return !(*this == other);
  }
  StringListIterator operator++() {
    cursor_ = cursor_->next_;
    return *this;
  }
  StringListIterator operator--() {
    cursor_ = cursor_->prev_;
    return *this;
  }
  std::string &operator*() { return cursor_->s_; }

private:
  StringListNode *cursor_;
};

class StringList {
public:
  StringList() : head_("<head>"), tail_("<tail>") {
    head_.next_ = &tail_;
    tail_.prev_ = &head_;
  }
  ~StringList() {
    StringListNode *cursor = head_.next_;
    while (cursor != &tail_) {
      StringListNode *next_cursor = cursor->next_;
      delete cursor;
      cursor = next_cursor;
    }
  }
  StringListIterator begin() { return StringListIterator(head_.next_); }
  StringListIterator end() { return StringListIterator(&tail_); }
  void push_back(const std::string &s) {
    StringListNode *new_node = new StringListNode(s);
    new_node->prev_ = tail_.prev_;
    new_node->next_ = &tail_;

    tail_.prev_->next_ = new_node;
    tail_.prev_ = new_node;
  }

private:
  StringListNode head_, tail_;
};

StringList string_split(const std::string &s);

int main() {
  StringList string_list =
      string_split("the quick brown fox jumps over the lazy dog");

  std::cout << "In forward order:\n";
  for (StringListIterator it = string_list.begin(); it != string_list.end();
       ++it) {
    std::cout << *it << "\n";
  }

  std::cout << "\nIn reverse order:\n";
  for (StringListIterator it = string_list.end(); it != string_list.begin();) {
    --it;
    std::cout << *it << "\n";
  }
}

StringList string_split(const std::string &s) {
  StringList string_list;

  std::string::const_iterator it = s.begin();
  while (it != s.end()) {
    it = std::find_if_not(it, s.end(), isspace);
    std::string::const_iterator jt = std::find_if(it, s.end(), isspace);
    if (it != jt) {
      string_list.push_back(std::string(it, jt));
    }
    it = jt;
  }

  return string_list;
}
