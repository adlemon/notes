// associative_containers.cpp
// Illustrates the use of associative containers.

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main() {
  std::cout << "std::map:\n";
  std::map<std::string, int> m;
  m["zero"] = 0;
  m["one"] = 1;
  m["two"] = 2;
  m["three"] = 3;
  for (const auto &kv : m) {
    std::cout << "key: " << kv.first << " -> value: " << kv.second << "\n";
  }

  std::cout << "\nstd::unordered_map:\n";
  std::unordered_map<std::string, int> uom;
  uom["zero"] = 0;
  uom["one"] = 1;
  uom["two"] = 2;
  uom["three"] = 3;
  for (const auto &kv : m) {
    std::cout << "key: " << kv.first << " -> value: " << kv.second << "\n";
  }

  std::cout << "\nstd::multimap:\n";
  std::multimap<int, std::string> mm;
  mm.insert({1, "one"});
  mm.insert({1, "unus"});
  mm.insert({2, "two"});
  mm.insert({2, "duo"});
  mm.insert({3, "three"});
  mm.insert({3, "tres"});
  for (const auto &kv : mm) {
    std::cout << "key: " << kv.first << " -> value: " << kv.second << "\n";
  }

  std::cout << "\nstd::unordered_multimap:\n";
  std::unordered_multimap<int, std::string> uomm;
  uomm.insert({1, "one"});
  uomm.insert({1, "unus"});
  uomm.insert({2, "two"});
  uomm.insert({2, "duo"});
  uomm.insert({3, "three"});
  uomm.insert({3, "tres"});
  for (const auto &kv : uomm) {
    std::cout << "key: " << kv.first << " -> value: " << kv.second << "\n";
  }

  std::cout << "\nstd::set:\n";
  std::set<std::string> s;
  s.insert("one");
  s.insert("two");
  s.insert("one");
  s.insert("two");
  for (const std::string &x : s) {
    std::cout << x << "\n";
  }

  std::cout << "\nstd::unordered_set:\n";
  std::unordered_set<std::string> uos;
  uos.insert("one");
  uos.insert("two");
  uos.insert("one");
  uos.insert("two");
  for (const std::string &x : uos) {
    std::cout << x << "\n";
  }

  std::cout << "\nstd::multiset:\n";
  std::multiset<std::string> ms;
  ms.insert("one");
  ms.insert("two");
  ms.insert("one");
  ms.insert("two");
  for (const std::string &x : ms) {
    std::cout << x << "\n";
  }

  std::cout << "\nstd::unordered_multiset:\n";
  std::unordered_multiset<std::string> uoms;
  uoms.insert("one");
  uoms.insert("two");
  uoms.insert("one");
  uoms.insert("two");
  for (const std::string &x : uoms) {
    std::cout << x << "\n";
  }
}
