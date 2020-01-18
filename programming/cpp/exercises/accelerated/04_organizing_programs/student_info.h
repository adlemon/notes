#ifndef STUDENT_INFO_H_
#define STUDENT_INFO_H_
// student_info.h
// Define a structure to hold information about the grades of a student in a
// course.

#include <iostream>
#include <string>
#include <vector>

struct StudentInfo {
  std::string name;
  double midterm_exam, final_exam;
  std::vector<double> homeworks;
};

bool compare(const StudentInfo& s1, const StudentInfo& s2);
std::istream& read(std::istream& in, StudentInfo& s);
std::istream& read_homeworks(std::istream& in, std::vector<double>& homeworks);

#endif
