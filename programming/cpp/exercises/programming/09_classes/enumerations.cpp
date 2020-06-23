// enumerations.cpp
// Illustrates the use of an enumeration.

#include <iostream>

enum class DayOfWeek {
  Sunday,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday
};

DayOfWeek operator+(DayOfWeek d, int n) { return DayOfWeek((int(d) + n) % 7); }
DayOfWeek operator+(int n, DayOfWeek d) { return DayOfWeek((int(d) + n) % 7); }

std::ostream &operator<<(std::ostream &os, DayOfWeek d) {
  switch (d) {
  case DayOfWeek::Sunday:
    os << "Sunday";
    break;
  case DayOfWeek::Monday:
    os << "Monday";
    break;
  case DayOfWeek::Tuesday:
    os << "Tuesday";
    break;
  case DayOfWeek::Wednesday:
    os << "Wednesday";
    break;
  case DayOfWeek::Thursday:
    os << "Thursday";
    break;
  case DayOfWeek::Friday:
    os << "Friday";
    break;
  case DayOfWeek::Saturday:
    os << "Saturday";
    break;
  }
  return os;
}

int main() {
  for (DayOfWeek d = DayOfWeek::Sunday;; d = d + 1) {
    std::cout << int(d) << ": " << d << "\n";

    if (d == DayOfWeek::Saturday) {
      break;
    }
  }
}
