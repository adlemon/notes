programs = \
	student_course_grade_class \
	student_course_grade_overall \
	student_course_grade_check_valid \
	student_course_grades_pass_fail \
	student_course_grades_pass_fail_sort \

all: $(programs)

%: %.cpp
	g++ $^ -o $@ --std=c++14

clean:
	rm -f $(programs)
