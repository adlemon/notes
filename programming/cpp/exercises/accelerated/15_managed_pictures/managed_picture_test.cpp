// managed_picture_test.cpp
// Example usage of the managed picture class.

#include <iostream>
#include <string>
#include <vector>

#include "managed_picture.cpp"

int main() {
  std::vector<std::string> lines;
  lines.push_back("hello");
  lines.push_back("world");

  Picture p = Picture(lines);
  Picture q = frame_fancy(p);
  Picture r = hcat(p, q);
  Picture s = vcat(q, r);
  std::cout << frame_fancy(hcat(s, vcat(r, q))) << std::endl;

  reframe_fancy(r, '#');
  reframe_fancy(q, '@');
  std::cout << frame_fancy(hcat(s, vcat(r, q)), '+', '-', '|') << std::endl;

  Picture p1 = Picture(std::vector<std::string>{" 11 "});
  Picture p2 = Picture(std::vector<std::string>{" 21 ", " 22 "});
  Picture p3 = Picture(std::vector<std::string>{" 31 ", " 32 ", " 33 "});
  Picture p4 =
      Picture(std::vector<std::string>{" 41 ", " 42 ", " 43 ", " 44 "});

  std::cout << std::string(80, '=') << "\n";
  std::cout << hcat_centered(p1, p3);
  std::cout << std::string(80, '=') << "\n";
  std::cout << hcat_centered(p3, p1);
  std::cout << std::string(80, '=') << "\n";
  std::cout << hcat_centered(p1, p4);
  std::cout << std::string(80, '=') << "\n";
  std::cout << hcat_centered(p4, p1);
  std::cout << std::string(80, '=') << "\n";
  std::cout << hcat_centered(p2, p4);
  std::cout << std::string(80, '=') << "\n";
  std::cout << hcat_centered(p4, p2);
  std::cout << std::string(80, '=') << "\n";
}
