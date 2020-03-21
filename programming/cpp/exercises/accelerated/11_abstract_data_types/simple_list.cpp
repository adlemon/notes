// simple_list.cpp
// A simple implementation of a list.

#include <algorithm>
#include <iostream>
#include <memory>

template <class T> class SimpleListNode {
public:
  SimpleListNode() : data(nullptr), prev(nullptr), next(nullptr) {}
  SimpleListNode(T *const data) : data(data), prev(nullptr), next(nullptr) {}

  T *data;
  SimpleListNode<T> *next, *prev;
};

template <class T> class SimpleListIterator {
public:
  SimpleListIterator() : node_(nullptr) {}
  SimpleListIterator(SimpleListNode<T> *const node) : node_(node) {}

  bool operator==(const SimpleListIterator &other) {
    return node_ == other.node_;
  }
  bool operator!=(const SimpleListIterator &other) { return !(*this == other); }
  SimpleListIterator &operator++() {
    if (node_) {
      node_ = node_->next;
    }
    return *this;
  }
  SimpleListIterator &operator--() {
    if (node_) {
      node_ = node_->prev;
    }
    node_ = node_->prev;
    return *this;
  }
  T &operator*() { return *(node_->data); }
  const T &operator*() const { return *(node_->data); }

private:
  SimpleListNode<T> *node_;

  template <class U> friend class SimpleList;
  template <class U> friend class SimpleListIterator;
};

template <class T> class SimpleList {
public:
  typedef SimpleListIterator<T> iterator;
  typedef SimpleListIterator<const T> const_iterator;
  typedef size_t size_type;
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;

  SimpleList() : head_(nullptr), tail_(nullptr), size_(0) {}
  explicit SimpleList(size_type n, const T &t = T());
  SimpleList(const SimpleList &other);
  SimpleList &operator=(const SimpleList &other);
  ~SimpleList() { clear(); }

  void push_back(const T &t);

  size_type size() const { return size_; }

  iterator begin() { return iterator(head_); }
  const_iterator begin() const { return const_iterator(head_); }
  iterator end() { return iterator(nullptr); }
  const_iterator end() const { return const_iterator(nullptr); }

  void clear();
  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);

private:
  SimpleListNode<T> *head_;
  SimpleListNode<T> *tail_;
  size_type size_;
  std::allocator<T> allocator_;
};

template <class T> void SimpleList<T>::push_back(const T &t) {
  T *data = allocator_.allocate(1);
  allocator_.construct(data, t);

  SimpleListNode<T> *node = new SimpleListNode<T>(data);
  ++size_;

  if (head_ == nullptr) {
    head_ = tail_ = node;
    return;
  }

  tail_->next = node;
  node->prev = tail_;
  tail_ = node;
}

template <class T>
typename SimpleList<T>::iterator SimpleList<T>::erase(iterator pos) {
  SimpleListNode<T> *node = pos.node_;
  ++pos;

  if (node == head_) {
    head_ = node->next;
  } else {
    node->prev->next = node->next;
  }

  if (node == tail_) {
    tail_ = node->prev;
  } else {
    node->next->prev = node->prev;
  }

  allocator_.destroy(node->data);
  allocator_.deallocate(node->data, 1);
  delete node;
  --size_;

  return pos;
}

template <class T>
typename SimpleList<T>::iterator SimpleList<T>::erase(iterator first,
                                                      iterator last) {
  while (first != last) {
    first = erase(first);
  }
  return last;
}

template <class T> void SimpleList<T>::clear() { erase(begin(), end()); }

template <class T>
std::ostream &operator<<(std::ostream &os, SimpleList<T> &lst);

int main() {
  SimpleList<int> lst;
  for (int i = 0; i < 10; ++i) {
    lst.push_back(i);
  }
  std::cout << lst << "\n";

  for (SimpleList<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
    if ((*it % 2) == 0) {
      it = lst.erase(it);
    }
  }
  std::cout << lst << "\n";

  for (SimpleList<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
    if ((*it % 3) == 0) {
      it = lst.erase(it);
    }
  }
  std::cout << lst << "\n";

  lst.clear();
  for (int i = 10; i < 20; ++i) {
    lst.push_back(i);
  }
  std::cout << lst << "\n";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, SimpleList<T> &lst) {
  os << "size = " << lst.size() << "\n";
  int i = 0;
  for (typename SimpleList<T>::iterator it = lst.begin(); it != lst.end();
       ++i, ++it) {
    os << "[" << i << "] => " << *it << "\n";
  }
  return os;
}
