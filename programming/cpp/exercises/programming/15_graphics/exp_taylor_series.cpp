// exp_taylor_series.cpp
// Draw Taylor-series approximations of the exponential function with
// progressively more terms.

#include <cmath>
#include <iostream>
#include <sstream>

#include "../stroustrup/Graph.h"
#include "../stroustrup/Simple_window.h"

constexpr int window_width = 600;
constexpr int window_height = 600;
constexpr int x_margin = 50;
constexpr int y_margin = 50;
constexpr int x_axis_min = -5;
constexpr int x_axis_max = +5;
constexpr int y_axis_min = -5;
constexpr int y_axis_max = +5;

double exp_taylor(double x, int n);
double exp_taylor_term(double x, int n);
double factorial_double(int n);

class CoordinateTransform {
public:
  CoordinateTransform(int in_min, int in_max, int out_min, int out_max)
      : in_min_(in_min), in_max_(in_max), out_min_(out_min), out_max_(out_max) {
  }
  int operator()(int in) {
    return ((in - in_min_) * out_max_ + (in_max_ - in) * out_min_) /
           (in_max_ - in_min_);
  }

private:
  int in_min_, in_max_, out_min_, out_max_;
};

int main() {
  CoordinateTransform xt{x_axis_min, x_axis_max, x_margin,
                         window_width - x_margin};
  CoordinateTransform yt{y_axis_min, y_axis_max, window_height - y_margin,
                         y_margin};

  Simple_window win{Point{100, 100}, window_width, window_height, "exp"};

  int x_axis_length = abs(xt(x_axis_max) - xt(x_axis_min));
  double x_axis_scale =
      static_cast<double>(x_axis_length) / (x_axis_max - x_axis_min);

  Axis x_axis{Axis::x,
              Point{xt(x_axis_min), (yt(y_axis_min) + yt(y_axis_max)) / 2},
              x_axis_length, x_axis_max - x_axis_min, "x"};
  x_axis.label.move(x_margin + 2 * x_axis_length / 3 + 5, -15);
  win.attach(x_axis);

  int y_axis_length = abs(yt(y_axis_max) - yt(y_axis_min));
  double y_axis_scale =
      static_cast<double>(y_axis_length) / (y_axis_max - y_axis_min);

  Axis y_axis{
      Axis::y, Point{(xt(x_axis_min) + xt(x_axis_max)) / 2, yt(y_axis_min)},
      abs(yt(y_axis_max) - yt(y_axis_min)), y_axis_max - y_axis_min, "y"};
  y_axis.label.move(5, 0);
  win.attach(y_axis);

  Function exp_graph{static_cast<double (*)(double)>(exp),
                     x_axis_min,
                     x_axis_max,
                     Point{xt(0), yt(0)},
                     100,
                     x_axis_scale,
                     y_axis_scale};
  exp_graph.set_color(Color::blue);
  exp_graph.set_style(Line_style(Line_style::solid, 4));
  win.attach(exp_graph);

  int exp_label_x = 2;
  int exp_label_y = 5;
  Text exp_label{Point{xt(exp_label_x), yt(exp_label_y)}, "exp(x)"};
  exp_label.set_color(exp_graph.color());
  win.attach(exp_label);

  win.wait_for_button();

  for (int n = 0; n <= 10; ++n) {
    Function exp_taylor_graph{
        [n](double x) -> double { return exp_taylor(x, n); },
        x_axis_min,
        x_axis_max,
        Point{xt(0), yt(0)},
        100,
        x_axis_scale,
        y_axis_scale};
    exp_taylor_graph.set_color(Color::red);
    exp_taylor_graph.set_style(Line_style(Line_style::dash, 2));

    std::ostringstream win_title;
    win_title << "exp[" << n << "]";
    win.set_label(win_title.str());

    win.attach(exp_taylor_graph);
    win.wait_for_button();
    win.detach(exp_taylor_graph);
  }
}

double exp_taylor(double x, int n) {
  double y = 0;
  for (int i = 0; i <= n; ++i) {
    y += exp_taylor_term(x, i);
  }
  return y;
}

double exp_taylor_term(double x, int n) {
  return pow(x, n) / factorial_double(n);
}

double factorial_double(int n) {
  double f = 1;
  for (int i = 1; i <= n; ++i) {
    f *= i;
  }
  return f;
}
