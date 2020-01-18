programs = \
	course_grade_functions \
	course_grade_structure \
	print_squares_100 \
	print_squares \
	print_squares_doubles \
	word_counts \
	course_grade_student_info \
	vector_double_avg \

all: $(programs)

%: %.cpp
	g++ $^ -o $@

median.o: median.h median.cpp
	g++ -c median.cpp

grade.o: student_info.h grade.h grade.cpp
	g++ -c grade.cpp

student_info.o: student_info.h student_info.cpp
	g++ -c student_info.cpp

course_grade_structure: median.o grade.o student_info.o course_grade_structure.cpp
	g++ $^ -o $@

clean:
	rm -f $(programs) *.o
