// pointer_set.cpp
// Deduplicate a vector of objects using a set of pointers.

#include <iostream>
#include <set>
#include <vector>

struct S {
  int i;
};

bool cmp(const S *x, const S *y) { return x->i < y->i; }

std::ostream &operator<<(std::ostream &os, const S x) { return os << x.i; }

int main() {
  constexpr int num_copies = 2;

  std::vector<S *> v;
  for (int i = 1; i <= 5; ++i) {
    for (int copy = 0; copy < num_copies; ++copy) {
      v.push_back(new S{i});
    }
  }

  std::set<S *, decltype(cmp) *> s(cmp);
  for (S *x : v) {
    s.insert(x);
  }

  bool is_first = true;
  for (S *x : s) {
    if (is_first) {
      is_first = false;
    } else {
      std::cout << ", ";
    }
    std::cout << *x;
  }
  std::cout << "\n";
}
