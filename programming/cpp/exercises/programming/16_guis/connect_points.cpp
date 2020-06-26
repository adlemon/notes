// connect_points.cpp
// GUI that reads points one at a time and adds each point to an open polyline
// as it is read.

#include <iostream>
#include <string>

#include "../stroustrup/GUI.h"
#include "../stroustrup/Window.h"

constexpr int window_width = 600;
constexpr int window_height = 400;
constexpr int button_width = 75;
constexpr int button_height = 20;
constexpr int button_sep = 10;
constexpr int box_width = 50;
constexpr int box_height = 20;
constexpr int box_sep = 75;

constexpr int quit_button_x = window_width - button_width;
constexpr int add_button_x = quit_button_x - button_sep - button_width;
constexpr int y_in_x = add_button_x - button_sep - box_width;
constexpr int x_in_x = y_in_x - 2 * button_sep - box_width;
constexpr int color_menu_x = window_width - button_width;
constexpr int color_menu_y = button_height + button_sep;

class ConnectPoints : public Graph_lib::Window {
public:
  ConnectPoints(Graph_lib::Point top_left, int width, int height,
                const std::string &title);

private:
  void next();
  void quit();
  void set_color(Graph_lib::Color c) {
    lines_.set_color(c);
    color_menu_.hide();
    show_color_menu_.show();
    redraw();
  }
  void show_color_menu() {
    show_color_menu_.hide();
    color_menu_.show();
  }

  Graph_lib::Open_polyline lines_;
  Graph_lib::Button add_button_;
  Graph_lib::Button quit_button_;
  Graph_lib::In_box x_in_;
  Graph_lib::In_box y_in_;
  Graph_lib::Out_box last_point_;
  Graph_lib::Button show_color_menu_;
  Graph_lib::Menu color_menu_;
};

int main() {
  try {
    ConnectPoints win{Graph_lib::Point{100, 100}, 600, 400,
                      "Connect the Points"};
    return Graph_lib::gui_main();
  } catch (exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "unknown exception" << std::endl;
    return 2;
  }
}

ConnectPoints::ConnectPoints(Graph_lib::Point top_left, int width, int height,
                             const std::string &title)
    : Window{top_left, width, height, title},
      add_button_{Graph_lib::Point{add_button_x, 0}, button_width,
                  button_height, "Add Point",
                  [](Graph_lib::Address, Graph_lib::Address pw) {
                    Graph_lib::reference_to<ConnectPoints>(pw).next();
                  }},
      quit_button_{Graph_lib::Point{quit_button_x, 0}, button_width,
                   button_height, "Quit",
                   [](Graph_lib::Address, Graph_lib::Address pw) {
                     Graph_lib::reference_to<ConnectPoints>(pw).quit();
                   }},
      x_in_{Graph_lib::Point{x_in_x, 0}, box_width, box_height, "x:"},
      y_in_{Graph_lib::Point{y_in_x, 0}, box_width, box_height, "y:"},
      last_point_{Graph_lib::Point{box_sep, 0}, 2 * box_width, box_height,
                  "last point:"},
      show_color_menu_{
          Graph_lib::Point{color_menu_x, color_menu_y}, button_width,
          button_height, "Color",
          [](Graph_lib::Address, Graph_lib::Address pw) {
            Graph_lib::reference_to<ConnectPoints>(pw).show_color_menu();
          }},
      color_menu_{Graph_lib::Point{color_menu_x, color_menu_y}, button_width,
                  button_height, Graph_lib::Menu::vertical, "color"} {
  attach(lines_);
  attach(add_button_);
  attach(quit_button_);
  attach(x_in_);
  attach(y_in_);
  attach(last_point_);
  attach(show_color_menu_);

  color_menu_.attach(new Graph_lib::Button{
      Graph_lib::Point{0, 0}, 0, 0, "red",
      [](Graph_lib::Address, Graph_lib::Address pw) {
        Graph_lib::reference_to<ConnectPoints>(pw).set_color(
            Graph_lib::Color::red);
      }});
  color_menu_.attach(new Graph_lib::Button{
      Graph_lib::Point{0, 0}, 0, 0, "blue",
      [](Graph_lib::Address, Graph_lib::Address pw) {
        Graph_lib::reference_to<ConnectPoints>(pw).set_color(
            Graph_lib::Color::blue);
      }});
  color_menu_.attach(new Graph_lib::Button{
      Graph_lib::Point{0, 0}, 0, 0, "black",
      [](Graph_lib::Address, Graph_lib::Address pw) {
        Graph_lib::reference_to<ConnectPoints>(pw).set_color(
            Graph_lib::Color::black);
      }});
  attach(color_menu_);
  color_menu_.hide();
}

void ConnectPoints::next() {
  try {
    int x = x_in_.get_int();
    int y = y_in_.get_int();
    lines_.add({x, y});

    std::ostringstream oss;
    oss << "(" << x << ", " << y << ")";
    last_point_.put(oss.str());

    redraw();
  } catch (...) {
    std::cerr << "failed to add inputs: "
              << "x: " << x_in_.get_string() << ", "
              << "y: " << y_in_.get_string() << std::endl;
  }
}

void ConnectPoints::quit() { hide(); }
