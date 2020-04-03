// map_copy.cpp
// Perform copy operations with a map.

#include <algorithm>
#include <map>
#include <string>
#include <vector>

int main() {
  std::map<int, std::string> m;
  m[1] = "one";
  m[2] = "two";
  m[3] = "three";

  std::vector<std::pair<int, std::string>> x;
  std::copy(m.begin(), m.end(), std::back_inserter(x));

  // The following lines fail to compile.
  // std::map<int, std::string> m2;
  // std::copy(x.begin(), x.end(), std::back_inserter(m2));
}
