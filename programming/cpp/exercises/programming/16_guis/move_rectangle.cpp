// move_rectangle.cpp
// Move a rectangle to a random location in the window when the user clicks a
// button.

#include <iostream>
#include <random>
#include <string>

#include "../stroustrup/GUI.h"
#include "../stroustrup/Window.h"

constexpr int window_width = 600;
constexpr int window_height = 400;
constexpr int button_width = 50;
constexpr int button_height = 20;
constexpr int button_sep = 10;
constexpr int rectangle_width = 60;
constexpr int rectangle_height = 40;

constexpr int move_button_x = window_width - button_width - button_sep;
constexpr int move_button_y = button_sep;
constexpr int quit_button_x = move_button_x;
constexpr int quit_button_y = move_button_y + button_height + button_sep;

inline int rand_int(int begin, int end) {
  static default_random_engine rng;
  return uniform_int_distribution<>{begin, end}(rng);
}

class MoveRectangle : public Graph_lib::Window {
public:
  MoveRectangle(Graph_lib::Point top_left, int width, int height,
                const string &title);

private:
  void move();
  void quit();

  Graph_lib::Button move_button_;
  Graph_lib::Button quit_button_;
  Graph_lib::Rectangle rect_;
};

int main() {
  try {
    MoveRectangle win{Graph_lib::Point{100, 100}, window_width, window_height,
                      "Move the Rectangle"};
    return Graph_lib::gui_main();
  } catch (exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "unknown error" << std::endl;
    return 2;
  }
}

MoveRectangle::MoveRectangle(Graph_lib::Point top_left, int width, int height,
                             const string &title)
    : Window{top_left, width, height, title},
      move_button_{Graph_lib::Point{move_button_x, move_button_y}, button_width,
                   button_height, "move",
                   [](Graph_lib::Address, Graph_lib::Address pw) {
                     Graph_lib::reference_to<MoveRectangle>(pw).move();
                   }},
      quit_button_{Graph_lib::Point{quit_button_x, quit_button_y}, button_width,
                   button_height, "quit",
                   [](Graph_lib::Address, Graph_lib::Address pw) {
                     Graph_lib::reference_to<MoveRectangle>(pw).quit();
                   }},
      rect_{Graph_lib::Point(0, 0), rectangle_width, rectangle_height} {
  move();
  attach(move_button_);
  attach(quit_button_);
  attach(rect_);
}

void MoveRectangle::move() {
  int newx = rand_int(0, window_width - rectangle_width);
  int newy = rand_int(0, window_height - rectangle_height);
  rect_.move(newx - rect_.point(0).x, newy - rect_.point(0).y);
  redraw();
}

void MoveRectangle::quit() { hide(); }
