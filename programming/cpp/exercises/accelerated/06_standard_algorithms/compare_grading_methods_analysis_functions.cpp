// compare_grading_methods_analysis_functions.cpp
// Compare the median grades in a course using different grading methods.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct StudentData {
  std::string name;
  double midterm_exam, final_exam;
  std::vector<double> homeworks;
};

std::istream& read(std::istream& in, StudentData& student);
bool did_all_hw(const StudentData& student);

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
);
double course_grade(
  const StudentData& student,
  double homework_avg(const std::vector<double>& homeworks)
);
double course_grade(
  const StudentData& student,
  double homework_avg(std::vector<double> homeworks)
);

double mean(const std::vector<double>& v);
double median(std::vector<double> v);
double median_nonzero(std::vector<double> v);

double course_grade_homework_median(const StudentData& student);
double course_grade_homework_mean(const StudentData& student);
double course_grade_homework_median_nonzero(const StudentData& student);

double median_course_grade(
  const std::vector<StudentData>& students,
  double course_grade(const StudentData& student)
);
void write_analysis(
  std::ostream& out,
  std::string analysis_name,
  double course_grade(const StudentData& student),
  const std::vector<StudentData>& students_all_hw,
  const std::vector<StudentData>& students_missing_hw
);

int main() {
  std::vector<StudentData> students_all_hw, students_missing_hw;

  StudentData student;
  while (read(std::cin, student)) {
    if (did_all_hw(student)) {
      students_all_hw.push_back(student);
    } else {
      students_missing_hw.push_back(student);
    }
    std::cout << '\n';
  }
  std::cout << '\n';

  if (students_all_hw.empty()) {
    std::cout << "\nNo student did all the homework.\n";
    return 1;
  }
  if (students_missing_hw.empty()) {
    std::cout << "\nEvery student did all the homework.\n";
    return 1;
  }

  std::cout << '\n';
  write_analysis(
    std::cout,
    "median",
    course_grade_homework_median,
    students_all_hw,
    students_missing_hw
  );

  write_analysis(
    std::cout,
    "mean",
    course_grade_homework_mean,
    students_all_hw,
    students_missing_hw
  );

  write_analysis(
    std::cout,
    "median_nonzero",
    course_grade_homework_median_nonzero,
    students_all_hw,
    students_missing_hw
  );
}

std::istream& read(std::istream& in, StudentData& student) {
  std::cout << "Enter the name of the student: ";
  if (!(in >> student.name)) {
    return in;
  }

  std::cout << "Enter the midterm exam grade for " << student.name << ": ";
  in >> student.midterm_exam;
  std::cout << "Enter the final exam grade for " << student.name << ": ";
  in >> student.final_exam;

  std::cout << "Enter the homework grades for " << student.name
            << " followed by an end-of-file: ";
  double homework;
  student.homeworks.clear();
  while (in >> homework) {
    student.homeworks.push_back(homework);
  }
  in.clear();

  return in;
}

bool did_all_hw(const StudentData& student) {
  return std::find(
    student.homeworks.begin(),
    student.homeworks.end(),
    0
  ) == student.homeworks.end();
}

double course_grade(
  double midterm_exam,
  double final_exam,
  double homework_avg
) {
  return 0.2 * midterm_exam + 0.4 * final_exam + 0.4 * homework_avg;
}

double course_grade(
  const StudentData& student,
  double homework_avg(const std::vector<double>& homeworks)
) {
  return course_grade(
    student.midterm_exam,
    student.final_exam,
    homework_avg(student.homeworks)
  );
}

double course_grade(
  const StudentData& student,
  double homework_avg(std::vector<double> homeworks)
) {
  return course_grade(
    student.midterm_exam,
    student.final_exam,
    homework_avg(student.homeworks)
  );
}

double mean(const std::vector<double>& v) {
  return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double median(std::vector<double> v) {
  std::sort(v.begin(), v.end());

  std::vector<double>::size_type n = v.size();
  std::vector<double>::size_type m = n / 2;
  return ((n % 2) == 0) ? (v[m-1] + v[m]) / 2 : v[m];
}

double median_nonzero(std::vector<double> v) {
  std::vector<double>::iterator end_nonzero = std::remove(
    v.begin(),
    v.end(),
    0
  );
  v.resize(end_nonzero - v.begin());
  return median(v);
}

double course_grade_homework_median(const StudentData& student) {
  return course_grade(student, median);
}

double course_grade_homework_mean(const StudentData& student) {
  return course_grade(student, mean);
}

double course_grade_homework_median_nonzero(const StudentData& student) {
  return course_grade(student, median_nonzero);
}

double median_course_grade(
  const std::vector<StudentData>& students,
  double course_grade(const StudentData& student)
) {
  std::vector<double> course_grades;
  std::transform(
    students.begin(),
    students.end(),
    std::back_inserter(course_grades),
    course_grade
  );

  return median(course_grades);
}

void write_analysis(
  std::ostream& out,
  std::string analysis_name,
  double course_grade(const StudentData& student),
  const std::vector<StudentData>& students_all_hw,
  const std::vector<StudentData>& students_missing_hw
) {
  out << analysis_name << ":"
    << " median(students_all_hw) = "
    << median_course_grade(students_all_hw, course_grade)
    << ", median(students_missing_hw) = "
    << median_course_grade(students_missing_hw, course_grade)
    << '\n';
}

