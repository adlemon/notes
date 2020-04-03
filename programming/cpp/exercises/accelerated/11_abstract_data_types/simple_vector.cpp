// simple_vector.cpp
// A simple implementation of a vector.

#include <algorithm>
#include <iostream>
#include <memory>

template <class T> class SimpleVector {
public:
  typedef T *iterator;
  typedef const T *const_iterator;
  typedef size_t size_type;
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;

  SimpleVector() { create(); }
  explicit SimpleVector(size_type n, const T &t = T()) { create(n, t); }
  SimpleVector(const SimpleVector &v) { create(v.begin(), v.end()); }
  SimpleVector(const_iterator b, const_iterator e) { create(b, e); }
  SimpleVector &operator=(const SimpleVector &other);
  ~SimpleVector() { uncreate(); }

  T &operator[](size_type i) { return begin_[i]; }
  const T &operator[](size_type i) const { return begin_[i]; }

  void push_back(const T &t) {
    if (end_ == buffer_end_) {
      grow();
    }
    unchecked_append(t);
  }

  size_type size() const { return end_ - begin_; }
  size_type capacity() const { return buffer_end_ - begin_; }

  iterator begin() { return begin_; }
  const_iterator begin() const { return begin_; }

  iterator end() { return end_; }
  const_iterator end() const { return end_; }

  void clear();
  void erase(const_iterator pos);
  void erase(const_iterator first, const_iterator last);

  void assign(T arr[], size_t n);

private:
  void create();
  void create(size_type n, const T &t);
  void create(const_iterator begin, const_iterator end);
  void uncreate();
  void grow();
  void unchecked_append(const T &t);

  iterator begin_;
  iterator end_;
  iterator buffer_end_;
  std::allocator<T> allocator_;
};

template <class T>
SimpleVector<T> &SimpleVector<T>::operator=(const SimpleVector &other) {
  if (&other != this) {
    uncreate();
    create(other.begin(), other.end());
  }
  return *this;
}

template <class T> void SimpleVector<T>::create() {
  begin_ = end_ = buffer_end_ = nullptr;
}

template <class T> void SimpleVector<T>::create(size_type n, const T &val) {
  begin_ = allocator_.allocate(n);
  end_ = buffer_end_ = begin_ + n;
  uninitialized_fill(begin_, buffer_end_, val);
}

template <class T>
void SimpleVector<T>::create(const_iterator i, const_iterator j) {
  begin_ = allocator_.allocate(j - i);
  end_ = buffer_end_ = uninitialized_copy(i, j, begin_);
}

template <class T> void SimpleVector<T>::uncreate() {
  if (begin_) {
    iterator it = end_;
    while (it != begin_) {
      --it;
      allocator_.destroy(it);
    }
    allocator_.deallocate(begin_, buffer_end_ - begin_);
  }
  begin_ = end_ = buffer_end_ = nullptr;
}

template <class T> void SimpleVector<T>::grow() {
  size_type new_size = std::max(2 * (buffer_end_ - begin_), std::ptrdiff_t(1));

  iterator new_begin_ = allocator_.allocate(new_size);
  iterator new_end_ = std::uninitialized_copy(begin_, end_, new_begin_);

  uncreate();

  begin_ = new_begin_;
  end_ = new_end_;
  buffer_end_ = begin_ + new_size;
}

template <class T> void SimpleVector<T>::unchecked_append(const T &val) {
  allocator_.construct(end_, val);
  ++end_;
}

template <class T> void SimpleVector<T>::clear() {
  iterator it = end_;
  while (it != begin_) {
    --it;
    allocator_.destroy(it);
  }
  end_ = begin_;
}

template <class T> void SimpleVector<T>::erase(const_iterator pos) {
  const_iterator it = pos;
  while (it != end_) {
    allocator_.destroy(it);
    allocator_.construct(it, it[1]);
    ++it;
  }
  allocator_.destroy(end_);
  --end_;
}

template <class T>
void SimpleVector<T>::erase(const_iterator first, const_iterator last) {
  const_iterator it = first, jt = last;
  while (it != last) {
    allocator_.destroy(it);
    allocator_.construct(it, *jt);
    allocator_.destroy(jt);
    ++it;
    ++jt;
  }
  end_ -= (last - first);
}

template <class T> void SimpleVector<T>::assign(T arr[], size_t n) {
  clear();
  for (size_t i = 0; i < n; ++i) {
    push_back(arr[i]);
  }
}

enum class VectorAction {
  Invalid,
  Print,
  PushBack,
  Update,
  Erase,
  EraseRange,
  Clear,
  Quit
};

VectorAction get_action();
void simple_vector_print(const SimpleVector<int> &v);
void simple_vector_push_back(SimpleVector<int> &v);
void simple_vector_update(SimpleVector<int> &v);
void simple_vector_erase(SimpleVector<int> &v);
void simple_vector_erase_range(SimpleVector<int> &v);
void simple_vector_clear(SimpleVector<int> &v);

int main() {
  SimpleVector<int> v;

  bool continue_repl = true;
  while (continue_repl) {
    switch (get_action()) {
    case VectorAction::Invalid:
      std::cout << "Invalid selection.\n\n";
      break;
    case VectorAction::Print:
      simple_vector_print(v);
      break;
    case VectorAction::PushBack:
      simple_vector_push_back(v);
      break;
    case VectorAction::Update:
      simple_vector_update(v);
      break;
    case VectorAction::Erase:
      simple_vector_erase(v);
      break;
    case VectorAction::EraseRange:
      simple_vector_erase_range(v);
      break;
    case VectorAction::Clear:
      simple_vector_clear(v);
      break;
    case VectorAction::Quit:
      continue_repl = false;
      break;
    }
  }

  {
    int arr[] = {1, 2, 3, 4, 5};
    SimpleVector<int> v;
    v.assign(arr, 5);
    std::cout << "v.size() = " << v.size() << "\n";
    for (SimpleVector<int>::size_type i = 0; i < v.size(); ++i) {
      std::cout << "v[" << i << "] = " << v[i] << "\n";
    }
  }
}

VectorAction get_action() {
  std::cout << "(1) Print the vector\n"
            << "(2) Push a new value onto the back of the vector\n"
            << "(3) Modifying an existing element of the vector\n"
            << "(4) Erase an element of the vector\n"
            << "(5) Erase a range of elements from the vector\n"
            << "(6) Clear the vector\n"
            << "(7) Quit\n"
            << "Choose an action: ";

  int a;
  std::cin >> a;
  std::cout << "\n";

  if (!(std::cin && 1 <= a && a <= 7)) {
    std::cin.clear();
    std::cin.ignore();
    return VectorAction::Invalid;
  }

  return static_cast<VectorAction>(a);
}

void simple_vector_print(const SimpleVector<int> &v) {
  if (v.size() == 0) {
    std::cout << "<empty>\n\n";
    return;
  }

  for (SimpleVector<int>::size_type i = 0; i < v.size(); ++i) {
    std::cout << "[" << i << "] => " << v[i] << "\n";
  }
  std::cout << "\n";
}

void simple_vector_push_back(SimpleVector<int> &v) {
  int val;
  std::cout << "Enter the value to append to the vector: ";
  if (!(std::cin >> val)) {
    std::cin.ignore();
    std::cin.clear();
    std::cout << "Invalid value.\n\n";
    return;
  }

  v.push_back(val);
  std::cout << "\n";
}

void simple_vector_update(SimpleVector<int> &v) {
  SimpleVector<int>::size_type i;
  std::cout << "Enter the index to update: ";
  if (!((std::cin >> i) && (i < v.size()))) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid index.\n\n";
    return;
  }

  int val;
  std::cout << "Enter the new value: ";
  if (!(std::cin >> val)) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid value.\n\n";
    return;
  }

  v[i] = val;
  std::cout << "\n";
}

void simple_vector_erase(SimpleVector<int> &v) {
  SimpleVector<int>::size_type i;
  std::cout << "Enter the index to erase: ";
  if (!((std::cin >> i) && (i < v.size()))) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid index.\n\n";
    return;
  }

  v.erase(v.begin() + i);
  std::cout << "\n";
}

void simple_vector_erase_range(SimpleVector<int> &v) {
  SimpleVector<int>::size_type i, j;
  std::cout << "Enter the first index in the range: ";
  if (!((std::cin >> i) && (i < v.size()))) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid index.\n\n";
  }

  std::cout << "Enter one past the last index in the range: ";
  if (!((std::cin >> j) && (i < j) && (j <= v.size()))) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Invalid index.\n\n";
  }

  v.erase(v.begin() + i, v.begin() + j);
  std::cout << "\n";
}

void simple_vector_clear(SimpleVector<int> &v) { v.clear(); }
