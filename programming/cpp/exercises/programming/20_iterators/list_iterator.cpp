// list_iterator.cpp
// Implements a simple list including an iterator class.

#include <iostream>

template <class T> class SimpleList {
public:
  SimpleList();
  ~SimpleList();

  class Iterator;

  Iterator begin();
  Iterator end();

  Iterator insert(Iterator i, const T &v);
  Iterator erase(Iterator i);

  void push_back(const T &v);
  void push_front(const T &v);
  void pop_front();
  void pop_back();

  T &front();
  T &back();

private:
  struct Node;
  Node *head_;
  Node *tail_;
};

template <class T> class SimpleList<T>::Iterator {
public:
  Iterator(SimpleList<T>::Node *node) : node_(node) {}

  Iterator &operator++() {
    node_ = node_->next;
    return *this;
  }
  Iterator &operator--() {
    node_ = node_->prev;
    return *this;
  }
  T &operator*() { return *(node_->value); }

  bool operator==(const Iterator &other) const { return node_ == other.node_; }
  bool operator!=(const Iterator &other) const { return !(*this == other); }

  friend class SimpleList<T>;

private:
  SimpleList<T>::Node *node_;
};

template <class T> struct SimpleList<T>::Node {
  Node() {}
  ~Node() { delete value; }
  T *value = nullptr;
  Node *prev = nullptr;
  Node *next = nullptr;
};

template <class T>
SimpleList<T>::SimpleList() : head_(new Node{}), tail_(new Node{}) {
  head_->next = tail_;
  tail_->prev = head_;
}

template <class T> SimpleList<T>::~SimpleList() {
  Node *cursor = head_;
  while (cursor) {
    Node *next_cursor = cursor->next;
    delete cursor;
    cursor = next_cursor;
  }
}

template <class T> typename SimpleList<T>::Iterator SimpleList<T>::begin() {
  return head_->next;
}

template <class T> typename SimpleList<T>::Iterator SimpleList<T>::end() {
  return tail_;
}

template <class T>
typename SimpleList<T>::Iterator SimpleList<T>::insert(Iterator i, const T &v) {
  Node *node = new Node{};
  node->value = new T{v};
  node->prev = i.node_;
  node->next = i.node_->next;
  node->prev->next = node;
  node->next->prev = node;
  return Iterator{node};
}

template <class T>
typename SimpleList<T>::Iterator SimpleList<T>::erase(Iterator i) {
  Iterator to_return = Iterator{i.node_->prev};
  i.node_->prev->next = i.node_->next;
  i.node_->next->prev = i.node_->prev;
  delete i.node_;
  return to_return;
}

template <class T> void SimpleList<T>::push_back(const T &v) {
  insert(tail_->prev, v);
}

template <class T> void SimpleList<T>::push_front(const T &v) {
  insert(head_, v);
}

template <class T> void SimpleList<T>::pop_front() { erase(head_->next); }

template <class T> void SimpleList<T>::pop_back() { erase(tail_->prev); }

template <class T> T &SimpleList<T>::front() { return head_->next->value; }

template <class T> T &SimpleList<T>::back() { return tail_->prev->value; }

template <class T>
std::ostream &operator<<(std::ostream &os, SimpleList<T> &lst) {
  bool is_first = true;
  for (typename SimpleList<T>::Iterator it = lst.begin(); it != lst.end();
       ++it) {
    if (is_first) {
      is_first = false;
    } else {
      os << " -> ";
    }
    os << *it;
  }
  return os;
}

int main() {
  SimpleList<int> lst;
  lst.push_front(2);
  lst.push_front(1);
  lst.push_back(3);
  lst.push_back(4);
  std::cout << lst << "\n";

  auto it2 = lst.begin();
  ++it2;
  lst.erase(it2);
  std::cout << lst << "\n";

  auto it3 = lst.end();
  --it3;
  --it3;
  lst.erase(it3);
  std::cout << lst << "\n";
}
