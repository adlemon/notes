// hcat_append.cpp
// Read two pictures from the user and concatenate them horizontally, where each
// line for each picture is the concatenation of all previous lines.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

typedef std::string picture_line;
typedef std::vector<picture_line> picture;

picture read_picture(std::istream& in);
void print_picture(std::ostream&, const picture& p);
picture_line::size_type picture_width(const picture& p);
picture hcat_accumulate(const picture& p1, const picture& p2);

int main() {
  std::cout << "Enter the first picture followed by an end-of-file:\n";
  picture p1 = read_picture(std::cin);

  std::cout << "\nEnter the second picture followed by an end-of-file:\n";
  picture p2 = read_picture(std::cin);

  std::cout << "\nThe horizontally accumulated concatenation "
            << "of the two pictures is:\n";
  print_picture(std::cout, hcat_accumulate(p1, p2));
}

picture read_picture(std::istream& in) {
  picture p;

  picture_line line;
  while (std::getline(in, line)) {
    p.push_back(line);
  }
  in.clear();

  return p;
}

void print_picture(std::ostream& out, const picture& p) {
  for (picture::const_iterator it = p.begin(); it != p.end(); ++it) {
    out << *it << '\n';
  }
}

picture_line::size_type picture_width(const picture& p) {
  picture_line::size_type width = 0;
  for (picture::const_iterator it = p.begin(); it != p.end(); ++it) {
    width = std::max(width, it->size());
  }
  return width;
}

picture hcat_accumulate(const picture& p1, const picture& p2) {
  picture p;
  picture_line line;
  picture_line::size_type width1 = picture_width(p1);

  picture::size_type i = 0;
  while (i < p1.size() || i < p2.size()) {
    if (i < p1.size()) {
      line += p1[i];
    }
    if (line.size() < width1) {
      line += picture_line(width1 - line.size(), ' ');
    }

    if (i < p2.size()) {
      line += p2[i];
    }

    p.push_back(line);
    i++;
  }

  return p;
}
