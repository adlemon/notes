// graphics_examples.cpp
// Draw a variety of objects in a graphics window.

#include <string>

#include "../stroustrup/Graph.h"
#include "../stroustrup/Simple_window.h"

constexpr double pi = 355.0 / 113.0;

constexpr int window_width = 600;
constexpr int window_height = 400;
const std::string window_title = "Graphics Examples";
constexpr int axis_length = 300;
constexpr int margin = 50;
constexpr int num_axis_ticks = 10;
constexpr int axis_tick_spacing =
    static_cast<double>(axis_length) / num_axis_ticks;

int main() {
  Point top_left{100, 100};
  Simple_window win{top_left, window_width, window_height, window_title};
  win.wait_for_button();

  // Draw axes.
  Axis x_axis{/*direction=*/Axis::x,
              /*start=*/Point{margin, window_height - margin},
              /*length=*/axis_length,
              /*num_ticks=*/num_axis_ticks, /*label=*/"x-axis"};
  Axis y_axis{/*direction=*/Axis::y,
              /*start=*/Point{margin, window_height - margin},
              /*length=*/axis_length,
              /*num_ticks=*/num_axis_ticks, /*label=*/"y-axis"};
  y_axis.set_color(Color::cyan);
  y_axis.label.set_color(Color::dark_red);

  win.attach(x_axis);
  win.attach(y_axis);
  win.set_label("+ Axes");
  win.wait_for_button();

  // Draw a graph of the sine function.
  Function sine_graph{
      /*fun=*/sin,
      /*range_start=*/0,
      /*range_end=*/3 * pi,
      /*origin=*/Point{margin, margin + axis_length / 2},
      /*count=*/1000,
      /*xscale=*/50,
      /*yscale=*/50};
  sine_graph.set_color(Color::blue);

  win.attach(sine_graph);
  win.set_label("+ Sine");
  win.wait_for_button();

  // Draw a triangle.
  Polygon triangle;
  triangle.add(Point{margin + axis_tick_spacing,
                     window_height - margin - axis_tick_spacing});
  triangle.add(Point{margin + 3 * axis_tick_spacing,
                     window_height - margin - axis_tick_spacing});
  triangle.add(Point{margin + 2 * axis_tick_spacing,
                     window_height - margin - 3 * axis_tick_spacing});

  triangle.set_color(Color::red);
  triangle.set_style(Line_style(Line_style::dash, 4));

  win.attach(triangle);
  win.set_label("+ Triangle");
  win.wait_for_button();

  // Draw a rectangle.
  Rectangle rectangle{Point{margin + 5 * axis_tick_spacing,
                            window_height - margin - 5 * axis_tick_spacing},
                      4 * axis_tick_spacing, 3 * axis_tick_spacing};
  rectangle.set_fill_color(Color::yellow);

  win.attach(rectangle);
  win.set_label("+ Rectangle");
  win.wait_for_button();

  // Draw a rectangular closed polyline.
  Closed_polyline rectangle_polyline;
  rectangle_polyline.add(Point{margin + axis_tick_spacing,
                               window_height - margin - 9 * axis_tick_spacing});
  rectangle_polyline.add(Point{margin + axis_tick_spacing,
                               window_height - margin - 7 * axis_tick_spacing});
  rectangle_polyline.add(Point{margin + 5 * axis_tick_spacing,
                               window_height - margin - 7 * axis_tick_spacing});
  rectangle_polyline.add(Point{margin + 5 * axis_tick_spacing,
                               window_height - margin - 9 * axis_tick_spacing});

  rectangle_polyline.set_style(Line_style(Line_style::dash, 2));
  rectangle_polyline.set_fill_color(Color::green);

  win.attach(rectangle_polyline);
  win.set_label("+ Rectangle 2");
  win.wait_for_button();

  // Add some text.
  Text txt{Point{margin + axis_length, window_height - margin},
           "Hello, World!"};
  txt.set_font(Graph_lib::Font::times_bold);
  txt.set_font_size(20);

  win.attach(txt);
  win.set_label("+ Text");
  win.wait_for_button();

  // Add an image.
  Image img{Point{margin + 6 * axis_tick_spacing, margin}, "smiley.jpg"};

  win.attach(img);
  win.set_label("+ Image");
  win.wait_for_button();

  // Add a mark.
  Mark mk{Point{margin + axis_tick_spacing,
                window_height - margin - axis_tick_spacing},
          'x'};

  win.attach(mk);
  win.set_label("+ Mark");
  win.wait_for_button();

  // Add a circle.
  Circle c{Point{margin + 2 * axis_tick_spacing,
                 window_height - margin - 2 * axis_tick_spacing},
           axis_tick_spacing};

  c.set_color(Color::green);
  c.set_style(Line_style(Line_style::solid, 4));

  win.attach(c);
  win.set_label("+ Circle");
  win.wait_for_button();

  // Add an ellipse.
  Ellipse e{Point{margin + 5 * axis_tick_spacing,
                  window_height - margin - 5 * axis_tick_spacing},
            4 * axis_tick_spacing, axis_tick_spacing};

  e.set_color(Color::red);
  e.set_style(Line_style(Line_style::solid, 4));

  win.attach(e);
  win.set_label("+ Ellipse");
  win.wait_for_button();

  // Move the image.
  img.move(3 * axis_tick_spacing, 0);

  win.set_label("Move");
  win.wait_for_button();
}
