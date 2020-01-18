// student_info.cpp
// Implement functions for a structure that holds information about the grades
// of a student in a course.

#include "student_info.h"

bool compare(const StudentInfo& s1, const StudentInfo& s2) {
  return s1.name < s2.name;
}

std::istream& read(std::istream& in, StudentInfo& s) {
  in >> s.name >> s.midterm_exam >> s.final_exam;
  read_homeworks(in, s.homeworks);
  return in;
}

std::istream& read_homeworks(std::istream& in, std::vector<double>& homeworks) {
  if (in) {
    homeworks.clear();

    double homework;
    while (in >> homework) {
      homeworks.push_back(homework);
    }

    in.clear();
  }

  return in;
}
