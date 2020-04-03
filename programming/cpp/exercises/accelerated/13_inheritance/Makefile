PROGRAMS = \
	course_grades_types_main \
	course_grades_types_constructors \
	course_grades_types_name_grade_calls \

FLAGS = \
	-std=c++17 \
	-Wall \
	-Wextra \
	-pedantic-errors \

all: $(PROGRAMS)

course_grades_types.o: course_grades_types.h course_grades_types.cpp
	g++ $(FLAGS) -c course_grades_types.cpp -o course_grades_types.o

%: %.cpp course_grades_types.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f $(PROGRAMS)
