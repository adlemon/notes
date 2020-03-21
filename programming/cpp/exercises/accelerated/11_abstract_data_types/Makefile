programs = \
	simple_vector \
	student_course_grades_instrumented \
	simple_list \

all: $(programs)

%: %.cpp
	g++ $^ -o $@ -std=c++17

clean:
	rm -f $(programs)
