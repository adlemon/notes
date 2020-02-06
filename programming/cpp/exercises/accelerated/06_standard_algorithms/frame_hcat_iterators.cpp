// frame_hcat_iterators.cpp
// Implement frame and hcat functions for word pictures using iterators.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

typedef std::string picture_line;
typedef std::vector<picture_line> picture;

std::istream& read(std::istream& in, picture& p);
picture_line::size_type width(const picture& p);
picture frame(const picture& p);
picture hcat(const picture& p1, const picture& p2);
void print(std::ostream& out, const picture& p);

int main() {
  picture p1, p2;

  std::cout << "Enter the first word picture followed by an end-of-file:\n";
  read(std::cin, p1);

  std::cout << "\nEnter the second word picture followed by an end-of-file:\n";
  read(std::cin, p2);

  std::cout << "\nThe horizontal concatenation of the framed pictures is:\n";
  print(std::cout, hcat(frame(p1), frame(p2)));
}

std::istream& read(std::istream& in, picture& p) {
  picture_line line;
  while (std::getline(in, line)) {
    p.push_back(line);
  }
  in.clear();

  return in;
}

picture_line::size_type width(const picture& p) {
  picture_line::size_type w = 0;

  for (picture::const_iterator it = p.begin(); it != p.end(); ++it) {
    w = std::max(w, it->size());
  }

  return w;
}

picture frame(const picture& p) {
  picture_line::size_type w = width(p);

  picture framed;
  framed.push_back(picture_line(w + 4, '*'));

  for (picture::const_iterator it = p.begin(); it != p.end(); ++it) {
    framed.push_back("* " + *it + picture_line(w - it->size(), ' ') + " *");
  }

  framed.push_back(framed[0]);
  return framed;
}

picture hcat(const picture& p1, const picture& p2) {
  picture_line::size_type w1 = width(p1);

  picture p;

  picture::const_iterator it1 = p1.begin(), it2 = p2.begin();
  while (it1 != p1.end() || it2 != p2.end()) {
    picture_line line;

    if (it1 != p1.end()) {
      line = *it1;
      ++it1;
    }
    line += picture_line(w1 - line.size(), ' ');

    if (it2 != p2.end()) {
      line += *it2;
      ++it2;
    }

    p.push_back(line);
  }

  return p;
}

void print(std::ostream& out, const picture& p) {
  for (picture::const_iterator it = p.begin(); it != p.end(); ++it) {
    out << *it << '\n';
  }
}
