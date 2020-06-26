// clock.cpp
// Draw a clock.

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>

#include "../stroustrup/GUI.h"
#include "../stroustrup/Window.h"

constexpr int window_size = 500;
constexpr int margin = 10;
constexpr int tick_length = 10;
constexpr int tick_end_radius = window_size / 2 - margin;
constexpr int tick_start_radius = tick_end_radius - tick_length;
constexpr int second_hand_length =
    window_size / 2 - 2 * margin - tick_length / 2;
constexpr int minute_hand_length = 3 * second_hand_length / 4;
constexpr int hour_hand_length = 3 * minute_hand_length / 4;
constexpr int button_width = 75;
constexpr int button_height = 25;
constexpr int button_sep = 10;

class Clock : public Graph_lib::Window {
public:
  Clock(Graph_lib::Point top_left, int width, int height, const string &title);
  void run();

private:
  void update();
  void update_hand(Graph_lib::Line *&hand, double revolution_fraction,
                   int hand_length);
  void start();
  void stop();
  void quit();

  bool run_ = false;
  Graph_lib::Point center_;
  Graph_lib::Lines ticks_;
  Graph_lib::Line *second_hand_;
  Graph_lib::Line *minute_hand_;
  Graph_lib::Line *hour_hand_;
  Graph_lib::Button start_button_;
  Graph_lib::Button stop_button_;
  Graph_lib::Button quit_button_;
};

int main() {
  try {
    Clock clock{Graph_lib::Point{100, 100}, window_size, window_size, "Clock"};
    clock.run();
    return Graph_lib::gui_main();
  } catch (exception &e) {
    std::cout << "exception: " << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cout << "unknown exception" << std::endl;
    return 2;
  }
}

Clock::Clock(Graph_lib::Point top_left, int width, int height,
             const string &title)
    : Window{top_left, width, height, title},
      center_{window_size / 2, window_size / 2}, second_hand_{nullptr},
      minute_hand_{nullptr}, hour_hand_{nullptr},
      start_button_{
          Graph_lib::Point{window_size - button_width - margin, margin},
          button_width, button_height, "start",
          [](Graph_lib::Address, Graph_lib::Address pw) {
            Graph_lib::reference_to<Clock>(pw).start();
          }},
      stop_button_{Graph_lib::Point{window_size - button_width - margin,
                                    margin + button_height + button_sep},
                   button_width, button_height, "stop",
                   [](Graph_lib::Address, Graph_lib::Address pw) {
                     Graph_lib::reference_to<Clock>(pw).stop();
                   }},
      quit_button_{Graph_lib::Point{window_size - button_width - margin,
                                    margin + 2 * (button_height + button_sep)},
                   button_width, button_height, "quit",
                   [](Graph_lib::Address, Graph_lib::Address pw) {
                     Graph_lib::reference_to<Clock>(pw).quit();
                   }} {
  for (int i = 0; i < 12; ++i) {
    double theta = 2.0 * 3.14 * (0.25 + i / 12.0);
    double cos_theta = cos(theta);
    double sin_theta = sin(theta);
    ticks_.add(
        Graph_lib::Point{
            static_cast<int>(center_.x + tick_start_radius * cos_theta),
            static_cast<int>(center_.y + tick_start_radius * sin_theta)},
        Graph_lib::Point{
            static_cast<int>(center_.x + tick_end_radius * cos_theta),
            static_cast<int>(center_.y + tick_end_radius * sin_theta)});
  }
  attach(ticks_);

  update();
  attach(start_button_);
  attach(stop_button_);
  attach(quit_button_);
}

void Clock::run() {
  run_ = true;
  while (run_) {
    update();
    Fl::wait(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

void Clock::update() {
  time_t ts = time(0);
  tm *t = localtime(&ts);

  update_hand(hour_hand_, t->tm_hour / 12.0, hour_hand_length);
  update_hand(minute_hand_, t->tm_min / 60.0, minute_hand_length);
  update_hand(second_hand_, t->tm_sec / 60.0, second_hand_length);
  redraw();
}

void Clock::update_hand(Graph_lib::Line *&hand, double revolution_fraction,
                        int hand_length) {
  if (hand) {
    detach(*hand);
    delete hand;
  }

  double theta = 2 * 3.14 * (0.25 - revolution_fraction);
  hand = new Graph_lib::Line{
      center_,
      {static_cast<int>(center_.x + hand_length * cos(theta)),
       static_cast<int>(center_.y - hand_length * sin(theta))}};
  attach(*hand);
}

void Clock::start() {
  run_ = true;
  run();
}

void Clock::stop() { run_ = false; }

void Clock::quit() {
  stop();
  hide();
}
