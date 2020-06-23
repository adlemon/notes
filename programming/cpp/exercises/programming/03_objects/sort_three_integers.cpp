// sort_three_integers.cpp
// Reads three integers from the standard input and prints them in sorted order.

#include <iostream>

int main() {
  int i1, i2, i3;
  std::cout << "Enter three integers: ";
  std::cin >> i1 >> i2 >> i3;

  // There are six possibilities.
  //   1: i1 <= i2 <= i3,
  //   2: i1 <= i3 < i2,
  //   3: i2 < i1 <= i3,
  //   4: i2 <= i3 < i1,
  //   5: i3 < i1 <= i2,
  //   6: i3 < i2 < i1.
  // Note that there is a unique permutation of i1, i2, and i3 that sorts these
  // variables if we first sort by the values of the integers, and then sort by
  // the names of these integers. These six possibilities correspond to the six
  // permutations that could be used to sort i1, i2, and i3 under this ordering.
  // We introduce the secondary sorting by the variable name in order to break
  // ties: if i1 == i2 == i3, then any of the six permutations of i1, i2, and i3
  // sorts these integers if we only consider the values of the variables, but
  // there is a unique permutation that sorts these integers if we use the names
  // of the variables as a secondary sort criterion. Having a unique permutation
  // that sorts each possibility makes it easier to decompose the problem into
  // mutually exclusive cases.
  int min, mid, max;
  if (i1 <= i2) {
    // We must be in one of the following cases:
    //   1: i1 <= i2 <= i3,
    //   2: i1 <= i3 < i2,
    //   5: i3 < i1 <= i2.
    if (i1 <= i3) {
      // We must be in one of the following cases:
      //   1: i1 <= i2 <= i3,
      //   2: i1 <= i3 < i2.
      if (i2 <= i3) {
        // We must be in the following case:
        //   1: i1 <= i2 <= i3.
        min = i1;
        mid = i2;
        max = i3;
      }
      if (i2 > i3) {
        // We must be in the following case:
        //   2: i1 <= i3 < i2.
        min = i1;
        mid = i3;
        max = i2;
      }
    }
    if (i1 > i3) {
      // We must be in the following case:
      //   5: i3 < i1 <= i2.
      min = i3;
      mid = i1;
      max = i2;
    }
  }
  if (i1 > i2) {
    // We must be in one of the following cases:
    //   3: i2 < i1 <= i3,
    //   4: i2 <= i3 < i1,
    //   6: i3 < i2 < i1.
    if (i1 <= i3) {
      // We must be in the following case:
      //   3: i2 < i1 <= i3.
      min = i2;
      mid = i1;
      max = i3;
    }
    if (i1 > i3) {
      // We must be in one of the following cases:
      //   4: i2 <= i3 < i1,
      //   6: i3 < i2 < i1.
      if (i2 <= i3) {
        // We must be in the following case:
        //   4: i2 <= i3 < i1.
        min = i2;
        mid = i3;
        max = i1;
      }
      if (i2 > i3) {
        // We must be in the following case:
        //   6: i3 < i2 < i1.
        min = i3;
        mid = i2;
        max = i1;
      }
    }
  }

  std::cout << "Sorting " << i1 << ", " << i2 << ", and " << i3
            << " in ascending order gives " << min << ", " << mid << ", and "
            << max << ".\n";
}
