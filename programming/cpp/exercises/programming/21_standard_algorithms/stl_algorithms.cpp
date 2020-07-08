// stl_algorithms.cpp
// Examples of some commonly used STL algorithms.

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  os << "[";
  bool is_first = true;
  for (auto &x : v) {
    if (is_first) {
      is_first = false;
    } else {
      os << ", ";
    }
    os << x;
  }
  return os << "]";
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::list<T> &lst) {
  bool is_first = true;
  for (auto &x : lst) {
    if (is_first) {
      is_first = false;
    } else {
      os << " -> ";
    }
    os << x;
  }
  return os;
}

class DistanceFrom {
public:
  DistanceFrom(int x) : x_(x) {}
  bool operator()(int i, int j) {
    int d_i = std::abs(i - x_);
    int d_j = std::abs(j - x_);
    return (d_i == d_j) ? (i < j) : (d_i < d_j);
  }

private:
  int x_;
};

bool is_even(int i) { return (i % 2) == 0; }

struct KeyValue {
  int key, value;
  // KeyValue(int key, int value): key(key), value(value) {}
  bool operator==(const KeyValue &other) { return key == other.key; }
};

bool operator<(const KeyValue &kv1, const KeyValue &kv2) {
  return kv1.key < kv2.key;
}

std::ostream &operator<<(std::ostream &os, const KeyValue &kv) {
  return os << kv.key << " [" << kv.value << "]";
}

int main() {
  // find.
  {
    std::cout << "std::find:\n";

    std::vector<int> v{3, 2, 1, 5, 1, 4};
    std::cout << "vector: " << v << "\n";

    for (auto x : {5, 6}) {
      auto it = std::find(v.begin(), v.end(), x);
      if (it == v.end()) {
        std::cout << "did not find: " << x << "\n";
      } else {
        std::cout << "found: " << *it << "\n";
      }
    }
  }

  // find_if.
  {
    std::cout << "\nstd::find_if:\n";

    std::list<std::string> lst{"abc", "abd", "tuv", "xyz"};
    std::cout << "list: " << lst << "\n";

    for (auto c : {'a', 'b'}) {
      auto it = std::find_if(lst.begin(), lst.end(), [c](const std::string &s) {
        return s.size() > 0 && s[0] == c;
      });
      if (it == lst.end()) {
        std::cout << "did not find string starting with " << c << "\n";
      } else {
        std::cout << "found string starting with " << c << ": " << *it << "\n";
      }
    }
  }

  // binary_search.
  {
    std::cout << "\nstd::binary_search:\n";

    std::vector<int> v{1, 3, 4, 6, 7, 9, 11};
    std::cout << "vector: " << v << "\n";

    for (int i : {7, 10}) {
      if (std::binary_search(v.begin(), v.end(), i)) {
        std::cout << "found: " << i << "\n";
      } else {
        std::cout << "did not find: " << i << "\n";
      }
    }
  }

  // count.
  {
    std::cout << "\nstd::count:\n";

    std::vector<int> v = {1, 1, 2, 1, 2, 3};
    std::cout << "vector: " << v << "\n";

    for (auto x : {1, 2, 3, 4}) {
      std::cout << "# of elements equal to " << x << ": "
                << std::count(v.begin(), v.end(), x) << "\n";
    }
  }

  // count_if.
  {
    std::cout << "\nstd::count_if:\n";

    std::list<int> lst{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "list: " << lst << "\n";

    std::cout << "# of even elements: "
              << std::count_if(lst.begin(), lst.end(), is_even) << "\n";
  }

  // sort.
  {
    std::cout << "\nstd::sort:\n";

    std::vector<int> v{2, 1, 5, 3, 4};
    std::cout << "vector: " << v << "\n";

    std::sort(v.begin(), v.end());
    std::cout << "sorted in default order: " << v << "\n";

    std::sort(v.begin(), v.end(), DistanceFrom{3});
    std::cout << "sorted by distance from 3: " << v << "\n";
  }

  // copy.
  {
    std::cout << "\nstd::copy:\n";

    std::list<int> lst{1, 2, 3, 4, 5};
    std::cout << "list: " << lst << "\n";

    std::vector<int> v(lst.size());
    std::copy(lst.begin(), lst.end(), v.begin());
    std::cout << "copy list to vector: " << v << "\n";
  }

  // copy_if.
  {
    std::cout << "\nstd::copy_if:\n";

    std::vector<int> v{1, 2, 3, 4, 5};
    std::cout << "vector: " << v << "\n";

    std::list<int> lst(std::count_if(v.begin(), v.end(), is_even));
    std::copy_if(v.begin(), v.end(), lst.begin(), is_even);
    std::cout << "copy vector to list if is_even: " << lst << "\n";
  }

  // merge.
  {
    std::cout << "\nstd::merge:\n";

    std::vector<int> v1{1, 2, 4, 7};
    std::vector<int> v2{3, 5, 6};
    std::cout << "vector 1: " << v1 << "\n"
              << "vector 2: " << v2 << "\n";

    std::list<int> lst(v1.size() + v2.size());
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), lst.begin());
    std::cout << "merge into list: " << lst << "\n";
  }

  // equal_range.
  {
    std::cout << "\nstd::equal_range, std::lower_bound, std::upper_bound:\n";

    std::list<KeyValue> lst{{1, 1}, {2, 1}, {3, 1}, {3, 2},
                            {3, 3}, {4, 1}, {5, 1}};
    std::cout << "list: " << lst << "\n";

    auto range = std::equal_range(lst.begin(), lst.end(), KeyValue{3, 0});
    std::cout << "range of values equal to 3: ";
    for (auto it = range.first; it != range.second; ++it) {
      if (it != range.first) {
        std::cout << ", ";
      }
      std::cout << *it;
    }
    std::cout << "\n";

    auto lower_bound = std::lower_bound(lst.begin(), lst.end(), KeyValue{3, 0});
    std::cout << "lower bound of values equal to 3: " << *lower_bound << "\n";

    auto upper_bound = std::upper_bound(lst.begin(), lst.end(), KeyValue{3, 0});
    std::cout << "upper bound of values equal to 3: " << *upper_bound << "\n";
  }

  // accumulate.
  {
    std::cout << "\naccumulate:\n";

    std::vector<int> v{1, 2, 3, 4, 5};
    std::cout << "vector: " << v << "\n";

    std::cout << "sum: " << std::accumulate(v.begin(), v.end(), 0) << "\n"
              << "product: "
              << std::accumulate(v.begin(), v.end(), 1,
                                 [](int x, int y) { return x * y; })
              << "\n";
  }

  // inner_product.
  {
    std::cout << "\ninner product:\n";

    std::vector<int> v{1, 2, 3, 4, 5};
    std::cout << "vector: " << v << "\n";
    std::list<int> lst{6, 7, 8, 9, 10};
    std::cout << "list: " << lst << "\n";

    std::cout << "sum of product of corresponding elements: "
              << std::inner_product(v.begin(), v.end(), lst.begin(), 0) << "\n"
              << "product of sum of corresponding elements: "
              << std::inner_product(lst.begin(), lst.end(), v.begin(), 1,
                                    [](int x, int y) { return x * y; },
                                    [](int x, int y) { return x + y; })
              << "\n";
  }
}
