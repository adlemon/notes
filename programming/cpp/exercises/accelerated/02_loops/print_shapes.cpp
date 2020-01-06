// print_shapes.cpp
// Print '*' characters in the shapes of a square, a rectangle, and a triangle
// to the console.

#include <iostream>
#include <string>

int main() {
  // Print a square.
  int square_side_length;
  std::cout << "Enter the side length of the square: ";
  std::cin >> square_side_length;

  std::cout << '\n';
  for (int r = 0; r < square_side_length; r++) {
    std::cout << std::string(square_side_length, '*') << '\n';
  }
  std::cout << std::endl;

  // Print a rectangle.
  int rectangle_width, rectangle_height;
  std::cout << "Enter the width of the rectangle: ";
  std::cin >> rectangle_width;
  std::cout << "Enter the height of the triangle: ";
  std::cin >> rectangle_height;

  std::cout << '\n';
  for (int r = 0; r < rectangle_height; r++) {
    std::cout << std::string(rectangle_width, '*') << '\n';
  }
  std::cout << std::endl;

  // Print a triangle.
  int triangle_height, triangle_width;
  std::cout << "Enter the width of the triangle: ";
  std::cin >> triangle_width;
  std::cout << "Enter the height of the triangle: ";
  std::cin >> triangle_height;

  std::cout << '\n';
  for (int r = 0; r < triangle_height; r++) {
    // r = 0 -> 1
    // r = triangle_height - 1 -> triangle_width
    // intercept = 1
    // slope = (triangle_width - 1) / (triangle_height - 1)
    int row_width = 1 + (r * (triangle_width - 1)) / (triangle_height - 1);
    std::cout << std::string(row_width, '*') << '\n';
  }
  std::cout << std::endl;
}
