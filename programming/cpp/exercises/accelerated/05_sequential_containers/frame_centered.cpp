// frame_centered.cpp
// Print a picture centered in a frame.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void print_picture(const std::vector<std::string> &picture);
std::string::size_type picture_width(const std::vector<std::string> &picture);
std::vector<std::string>
frame_centered(const std::vector<std::string> &picture);

int main() {
  std::vector<std::string> picture;
  std::string line;
  std::cout << "Enter the picture followed by an end-of-file:\n";
  while (std::getline(std::cin, line)) {
    picture.push_back(line);
  }

  std::cout << '\n';
  print_picture(frame_centered(picture));
}

void print_picture(const std::vector<std::string> &picture) {
  for (std::vector<std::string>::const_iterator it = picture.begin();
       it != picture.end(); ++it) {
    std::cout << *it << '\n';
  }
}

std::string::size_type picture_width(const std::vector<std::string> &picture) {
  std::string::size_type width = 0;

  for (std::vector<std::string>::const_iterator it = picture.begin();
       it != picture.end(); ++it) {
    width = std::max(width, it->size());
  }

  return width;
}
std::vector<std::string>
frame_centered(const std::vector<std::string> &picture) {
  std::string::size_type width = picture_width(picture);

  std::vector<std::string> framed_picture;
  framed_picture.push_back(std::string(width + 4, '*'));
  for (std::vector<std::string>::const_iterator it = picture.begin();
       it != picture.end(); ++it) {
    std::string::size_type left_pad = (width - it->size()) / 2;
    framed_picture.push_back("* " + std::string(left_pad, ' ') + *it +
                             std::string(width - left_pad - it->size(), ' ') +
                             " *");
  }
  framed_picture.push_back(framed_picture[0]);

  return framed_picture;
}
