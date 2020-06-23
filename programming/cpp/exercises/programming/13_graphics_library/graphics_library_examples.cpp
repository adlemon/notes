// graphics_library_examples.cpp
// Draw a variety of objects in a graphics window using the graphics library.

#include <sstream>

#include "../stroustrup/Graph.h"
#include "../stroustrup/Simple_window.h"

constexpr int win_top = 100;
constexpr int win_left = 100;
constexpr int win_width = 600;
constexpr int win_height = 400;

int main() {
  // Create the graphics window.
  Simple_window win{Point{win_left, win_top}, win_width, win_height,
                    "Graphics Window"};
  win.wait_for_button();

  // Draw a line.
  Line line{Point{50, 50}, {win_width - 50, win_height - 50}};

  win.set_label("Line");
  win.attach(line);
  win.wait_for_button();
  win.detach(line);

  // Draw multiple lines that uses color and a line style.
  Lines lines;
  int lines_spacing = win_width / 10;
  for (int x = lines_spacing; x < win_width; x += lines_spacing) {
    lines.add(Point{x, 0}, Point{x, win_height});
  }
  for (int y = lines_spacing; y < win_height; y += lines_spacing) {
    lines.add(Point{0, y}, Point{win_width, y});
  }
  lines.set_color(Color::red);
  lines.set_style(Line_style{Line_style::dash, 2});

  win.set_label("Lines");
  win.attach(lines);
  win.wait_for_button();
  win.detach(lines);

  // Draw an open polyline.
  Open_polyline opl;
  opl.add(Point{50, 50});
  opl.add(Point{50, win_height - 50});
  opl.add(Point{win_width - 50, 50});
  opl.add(Point{win_width - 50, win_height - 50});

  win.set_label("Open Polyline");
  win.attach(opl);
  win.wait_for_button();
  win.detach(opl);

  // Draw a filled closed polyline.
  Closed_polyline cpl;
  cpl.add(Point{50, 50});
  cpl.add(Point{50, win_height - 50});
  cpl.add(Point{win_width - 50, 50});
  cpl.add(Point{win_width - 50, win_height - 50});

  win.set_label("Closed Polyline");
  win.attach(cpl);
  win.wait_for_button();
  win.detach(cpl);

  // Draw marks.
  Marks mks{"o"};
  mks.add(Point{50, 50});
  mks.add(Point{50, win_height - 50});

  Mark mk{Point{win_width - 50, win_height - 50}, 'x'};

  win.set_label("Marks");
  win.attach(mks);
  win.attach(mk);
  win.wait_for_button();
  win.detach(mks);
  win.detach(mk);

  // Draw a marked polyline.
  Marked_polyline mpl{"xo"};
  mpl.add(Point{50, 50});
  mpl.add(Point{50, win_height - 50});
  mpl.add(Point{win_width - 50, win_height - 50});

  win.set_label("Marked Polyline");
  win.attach(mpl);
  win.wait_for_button();
  win.detach(mpl);

  // Draw a polygon.
  Polygon pgon;
  pgon.add(Point{50, 50});
  pgon.add(Point{50, win_height - 50});
  pgon.add(Point{win_width - 50, win_height - 50});
  pgon.add(Point{win_width - 50, 50});

  win.set_label("Polygon");
  win.attach(pgon);
  win.wait_for_button();
  win.detach(pgon);

  // Draw rectangles.
  Rectangle rect1{Point{50, 50}, Point{win_width - 50, win_height - 50}};
  Rectangle rect2{Point{100, 100}, win_width - 200, win_height - 200};

  win.set_label("Rectangles");
  win.attach(rect1);
  win.attach(rect2);
  win.wait_for_button();
  win.detach(rect1);
  win.detach(rect2);

  // Draw a color palette.
  Vector_ref<Rectangle> palette;
  Vector_ref<Text> palette_labels;
  int palette_grid_size = 25;
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      int color_index = 16 * i + j;

      palette.push_back(
          new Rectangle{Point{palette_grid_size * i, palette_grid_size * j},
                        palette_grid_size, palette_grid_size});
      palette[palette.size() - 1].set_fill_color(Color{color_index});

      std::stringstream ss;
      ss << color_index;
      palette_labels.push_back(
          new Text{Point{static_cast<int>(palette_grid_size * (i + 0.2)),
                         static_cast<int>(palette_grid_size * (j + 0.75))},
                   ss.str()});
      palette_labels[palette_labels.size() - 1].set_font_size(10);
      palette_labels[palette_labels.size() - 1].set_font(
          Graph_lib::Font::helvetica);
    }
  }

  win.set_label("Colors");
  for (int i = 0; i < palette.size(); ++i) {
    win.attach(palette[i]);
    win.attach(palette_labels[i]);
  }
  win.wait_for_button();
  for (int i = 0; i < palette.size(); ++i) {
    win.detach(palette[i]);
    win.detach(palette_labels[i]);
  }

  // Draw circles and ellipses.
  Circle circ{Point{win_width / 2, win_height / 2}, 10};
  Ellipse ell_circ{Point{win_width / 2, win_height / 2}, 20, 20};
  Ellipse ell_ecc{Point{win_width / 2, win_height / 2}, 40, 80};

  win.set_label("Ellipses");
  win.attach(circ);
  win.attach(ell_circ);
  win.attach(ell_ecc);
  win.wait_for_button();
  win.detach(circ);
  win.detach(ell_circ);
  win.detach(ell_ecc);

  // Show an image.
  Image img{Point{50, 50}, "smiley.jpg"};

  win.set_label("Image");
  win.attach(img);
  win.wait_for_button();
  win.detach(img);
}
