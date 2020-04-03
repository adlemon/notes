// frame_picture.cpp
// Read three sets of lines from the user. Frame all three sets of lines. Then
// concatenate the first two sets of lines horizontally, concatenate the
// resulting picture vertically with the third set of lines, and print the
// result.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void print_picture(std::vector<std::string> picture);
std::string::size_type width(std::vector<std::string> picture);
std::vector<std::string> frame(std::vector<std::string> picture);
std::vector<std::string> hcat(std::vector<std::string> left,
                              std::vector<std::string> right);
std::vector<std::string> vcat(std::vector<std::string> top,
                              std::vector<std::string> bottom);

int main() {
  std::vector<std::vector<std::string>> pictures(3);

  for (int i = 0; i < 3; i++) {
    std::string s;
    std::cout << "Enter the contents of picture " << i + 1 << ":\n";
    while (std::getline(std::cin, s)) {
      pictures[i].push_back(s);
    }
    std::cin.clear();
  }

  std::cout << "\nThe collage is as follows.\n";
  print_picture(
      vcat(hcat(frame(pictures[0]), frame(pictures[1])), frame(pictures[2])));
}

void print_picture(std::vector<std::string> picture) {
  for (std::vector<std::string>::const_iterator it = picture.begin();
       it < picture.end(); ++it) {
    std::cout << *it << '\n';
  }
}

std::string::size_type width(std::vector<std::string> picture) {
  std::string::size_type w = 0;
  for (std::vector<std::string>::const_iterator it = picture.begin();
       it < picture.end(); ++it) {
    w = std::max(it->size(), w);
  }
  return w;
}

std::vector<std::string> frame(std::vector<std::string> picture) {
  std::string::size_type w = width(picture);

  std::vector<std::string> framed;
  framed.push_back(std::string(w + 4, '*'));
  for (std::vector<std::string>::const_iterator it = picture.begin();
       it < picture.end(); ++it) {
    framed.push_back("* " + *it + std::string(w - it->size(), ' ') + " *");
  }
  framed.push_back(framed[0]);

  return framed;
}

std::vector<std::string> hcat(std::vector<std::string> left,
                              std::vector<std::string> right) {
  std::string::size_type left_width = width(left);

  std::vector<std::string> picture;
  std::vector<std::string>::size_type i = 0, j = 0;
  while (i < left.size() || j < right.size()) {
    std::string line;

    if (i < left.size()) {
      line += left[i];
      i++;
    }

    line += std::string(left_width - line.size(), ' ');

    if (j < right.size()) {
      line += right[j];
      j++;
    }

    picture.push_back(line);
  }
  return picture;
}

std::vector<std::string> vcat(std::vector<std::string> top,
                              std::vector<std::string> bottom) {
  std::vector<std::string> picture = top;
  picture.insert(picture.end(), bottom.begin(), bottom.end());
  return picture;
}
