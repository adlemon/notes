// library_templates.cpp
// Implement library functions using templates.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

namespace my {
// swap(x, y)
// Swap the values of the variables x and y.
template <class T>
void swap(T& x, T& y) {
  T tmp = x;
  x = y;
  y = tmp;
}

// equal(b, e, b2)
// Returns true if every element in the range [b, e) is equal to the
// corresponding element in the range [b2, b2 + (e - b2)) and false otherwise.
template <class It1, class It2>
bool equal(It1 b, It1 e, It2 b2) {
  while (b != e) {
    if (*b != *b2) {
      return false;
    }
    ++b;
    ++b2;
  }
  return true;
}

// search(b, e, b2, e2)
// Returns the first iterator in the range [b, e) that marks the beginning of a
// subsequence of [b, e) whose values are equal to the corresponding values in
// the range [b2, e2).
template <class It1, class It2>
It1 search(It1 b, It1 e, It2 b2, It2 e2) {
  while (b != e) {
    It1 i = b;
    It2 i2 = b2;
    while (i != e && i2 != e2 && *i == *i2) {
      ++i;
      ++i2;
    }

    if (i2 == e2) {
      return b;
    }

    ++b;
  }
  return b;
}

// find(b, e, t)
// Returns the first iterator in the range [b, e) whose value is equal to t, or
// e if there is no iterator in the range [b, e) whose value is equal to t.
template <class It, class Val>
It find(It b, It e, Val t) {
  while (b != e && *b != t) {
    ++b;
  }
  return b;
}

// find_if(b, e, p)
// Returns the first iterator in the range [b, e) whose value satisfies the
// predicate p, or e if there is no iterator in the range [b, e) whose value
// satisfies the predicate p.
template <class It, class Pred>
It find_if(It b, It e, Pred p) {
  while (b != e && !p(*b)) {
    ++b;
  }
  return b;
}

// copy(b, e, d)
// Copies all elements from the range [b, e) to the destination d.
template <class In, class Out>
void copy(In b, In e, Out d) {
  while (b != e) {
    *d = *b;
    ++b;
    ++d;
  }
}

// remove_copy(b, e, d, t)
// Copies all elements whose values are not equal to t from the range [b, e) to
// the destination d.
template <class In, class Out, class Val>
void remove_copy(In b, In e, Out d, Val t) {
  while (b != e) {
    if (*b != t) {
      *d = *b;
      ++d;
    }
    ++b;
  }
}

// remove_copy_if(b, e, d, p)
// Copies all elements that do not satisfy the predicate p from the range
// [b, e) to the destination d.
template <class In, class Out, class Pred>
void remove_copy_if(In b, In e, Out d, Pred p) {
  while (b != e) {
    if (!p(*b)) {
      *d = *b;
      ++d;
    }
    ++b;
  }
}

// remove(b, e, t)
// Rearranges the elements of the range [b, e) so that all values of t occur at
// the end of the container, and returns an iterator pointing to the first
// element whose value is equal to t (or e if there is no element whose value
// is not equal to t).
template <class It, class Val>
It remove(It b, It e, Val t) {
  // We define a "write cursor" w to keep track of where the next value of t
  // should be added.
  It w = b;
  while (b != e) {
    if (*b != t) {
      swap(*b, *w);
      ++w;
    }
    ++b;
  }
  return w;
}

// transform(b, e, d, f)
// Apply the function f to every element in the range [b, e), and write the
// results to d.
template <class In, class Out, class Fun>
void transform(In b, In e, Out d, Fun f) {
  while (b != e) {
    *d = f(*b);
    ++b;
    ++d;
  }
}

// partition(b, e, p)
// Rearranges the elements of the range [b, e) so that those elements for which
// the predicate p returns true are at the front of the container, and returns
// an iterator to the first element for which the predicate returns false (or to
// e if there is no element for which the predicate returns false).
template <class It, class Pred>
It partition(It b, It e, Pred p) {
  // Maintain a cursor with the location where we should put the next element
  // for which the predicate returns true.
  It w = b;
  while (b != e) {
    if (p(*b)) {
      swap(*w, *b);
      ++w;
    }
    ++b;
  }
  return w;
}

// accumulate(b, e, t)
// Returns the sum of all values in the range [b, e) starting from the initial
// value t. The returned value has the same type as t.
template <class It, class Val>
Val accumulate(It b, It e, Val t) {
  while (b != e) {
    t += *b;
    ++b;
  }
  return t;
}

} // namespace my

bool is_even(const int x) {
  return (x % 2) == 0;
}

bool is_odd(const int x) {
  return (x % 2) == 1;
}

template <class Cont>
void print(const Cont& c) {
  std::copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " "));
}

int square(int x) {
  return x * x;
}

int main() {
  {
    std::cout << "Test for swap(x, y):\n";
    int x = 1, y = 2;
    std::cout << "before: x = " << x << ", y = " << y << "\n";
    my::swap(x, y);
    std::cout << "after:  x = " << x << ", y = " << y << "\n";
  }

  {
    std::cout << "\nTest for equal(b, e, b2):\n";
    std::vector<int> v;
    std::list<int> lst;
    for (int i = 1; i <= 3; ++i) {
      v.push_back(i);
      lst.push_back(i);
    }

    std::cout << "v = ";
    print(v);
    std::cout << ", lst = ";
    print(lst);
    std::cout << "\n";

    std::cout << "equal(v.begin(), v.end(), lst.begin()) => "
              << my::equal(v.begin(), v.end(), lst.begin())
              << "\n";
  }

  {
    std::cout << "\nTest for equal(b, e, b2):\n";
    std::vector<int> v;
    std::list<int> lst;
    for (int i = 1; i <= 3; ++i) {
      v.push_back(i);
      lst.push_back((i < 3) ? i : (i + 1));
    }

    std::cout << "v = ";
    print(v);
    std::cout << ", lst = ";
    print(lst);
    std::cout << "\n";

    std::cout << "equal(v.begin(), v.end(), lst.begin()) => "
              << my::equal(v.begin(), v.end(), lst.begin())
              << "\n";
  }

  {
    std::cout << "\nTest for search(b, e, b2, e2):\n";
    std::vector<int> v;
    std::list<int> lst;
    for (int i = 1; i <= 5; ++i) {
      v.push_back(i);
      if (1 < i && i < 5) {
        lst.push_back(i);
      }
    }

    std::cout << "v = ";
    print(v);
    std::cout << ", lst = ";
    print(lst);
    std::cout << "\n";

    std::vector<int>::const_iterator s = my::search(
      v.begin(),
      v.end(),
      lst.begin(),
      lst.end()
    );
    std::cout << "search(v.begin(), v.end(), lst.begin(), lst.end()) => "
              << ((s != v.end()) ? "found" : "not found")
              << "\n";
  }

  {
    std::cout << "\nTest for search(b, e, b2, e2):\n";
    std::vector<int> v;
    std::list<int> lst;
    for (int i = 1; i <= 6; ++i) {
      v.push_back(i);
      if ((2 <= i && i <= 3) || (i == 5)) {
        lst.push_back(i);
      }
    }

    std::cout << "v = ";
    print(v);
    std::cout << ", lst = ";
    print(lst);
    std::cout << "\n";

    std::vector<int>::const_iterator s = my::search(
      v.begin(),
      v.end(),
      lst.begin(),
      lst.end()
    );
    std::cout << "search(v.begin(), v.end(), lst.begin(), lst.end()) => "
              << ((s != v.end()) ? "found" : "not found")
              << "\n";
  }

  {
    std::cout << "\nTest for find(b, e, t):\n";
    std::vector<int> v;
    for (int i = 1; i <= 3; ++i) {
      v.push_back(i);
    }

    std::cout << "v = ";
    print(v);
    std::cout << "\n";

    std::vector<int>::const_iterator i2 = my::find(v.begin(), v.end(), 2);
    std::vector<int>::const_iterator i4 = my::find(v.begin(), v.end(), 4);
    std::cout << "find(v.begin(), v.end(), 2) => "
              << ((i2 == v.end()) ? "not found" : "found") << "\n"
              << "find(v.begin(), v.end(), 4) => "
              << ((i4 == v.end()) ? "not found" : "found") << "\n";
  }

  {
    std::cout << "\nTest for find(b, e, p):\n";
    std::vector<int> v;
    for (int i = 1; i <= 3; ++i) {
      v.push_back(2 * i);
    }

    std::cout << "v = ";
    print(v);
    std::cout << "\n";

    std::vector<int>::const_iterator i_even = my::find_if(
      v.begin(),
      v.end(),
      is_even
    );
    std::vector<int>::const_iterator i_odd = my::find_if(
      v.begin(),
      v.end(),
      is_odd
    );

    std::cout << "find_if(v.begin(), v.end(), is_even) => "
              << ((i_even != v.end()) ? "found" : "not found") << "\n"
              << "find_if(v.begin(), v.end(), is_odd) => "
              << ((i_odd != v.end()) ? "found" : "not found") << "\n";
  }

  {
    std::cout << "\nTest for copy(b, e, d):\n";
    std::vector<int> v;
    for (int i = 1; i <= 3; ++i) {
      v.push_back(i);
    }
    std::cout << "v = ";
    print(v);
    std::cout << "\n";

    std::list<int> lst;
    my::copy(v.begin(), v.end(), std::back_inserter(lst));
    std::cout << "lst = ";
    print(lst);
    std::cout << "\n";
  }

  {
    std::cout << "\nTest for remove_copy(b, e, d, t):\n";
    std::vector<int> v;
    for (int i = 1; i <= 4; ++i) {
      v.push_back(i);
    }

    std::cout << "v = ";
    print(v);
    std::cout << "\n";

    std::list<int> lst;
    my::remove_copy(v.begin(), v.end(), std::back_inserter(lst), 2);
    std::cout << "lst = ";
    print(lst);
    std::cout << "\n";
  }

  {
    std::cout << "\nTest for remove_copy_if(b, e, p):\n";
    std::vector<int> v;
    for (int i = 1; i <= 6; ++i) {
      v.push_back(i);
    }

    std::cout << "v = ";
    print(v);
    std::cout << "\n";

    std::list<int> lst;
    my::remove_copy_if(v.begin(), v.end(), std::back_inserter(lst), is_even);
    std::cout << "lst = ";
    print(lst);
    std::cout << "\n";
  }

  {
    std::cout << "\nTest for remove(b, e, t):\n";
    std::vector<int> v;
    for (int i = 1; i <= 5; ++i) {
      v.push_back(i);
    }

    std::cout << "before: v = ";
    print(v);
    std::cout << "\n";

    my::remove(v.begin(), v.end(), 2);
    std::cout << "after: v = ";
    print(v);
    std::cout << "\n";
  }

  {
    std::cout << "\nTest for transform(b, e, d, f):\n";
    std::vector<int> v;
    for (int i = 1; i <= 5; ++i) {
      v.push_back(i);
    }

    std::cout << "v = ";
    print(v);
    std::cout << "\n";

    std::list<int> lst;
    my::transform(v.begin(), v.end(), std::back_inserter(lst), square);

    std::cout << "lst = ";
    print(lst);
    std::cout << "\n";
  }

  {
    std::cout << "\nTest for partition(b, e, p):\n";
    std::vector<int> v;
    for (int i = 1; i <= 6; ++i) {
      v.push_back(i);
    }

    std::cout << "before: v = ";
    print(v);
    std::cout << "\n";

    partition(v.begin(), v.end(), is_even);
    std::cout << "after: v = ";
    print(v);
    std::cout << "\n";
  }

  {
    std::cout << "\nTest for accumulate:\n";
    std::vector<int> v;
    for (int i = 1; i <= 10; ++i) {
      v.push_back(i);
    }

    std::cout << "v = ";
    print(v);
    std::cout << "\n";

    int total = my::accumulate(v.begin(), v.end(), 0);
    std::cout << "total = " << total << "\n";
  }
}
