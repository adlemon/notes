programs = \
	simple_vector_test \
	student_course_grades_instrumented \
	simple_list \

all: $(programs)

simple_vector.o: simple_vector.cpp
	g++ -c $^ -o $@ -std=c++17

%: %.cpp simple_vector.o
	g++ $^ simple_vector.o -o $@ -std=c++17

clean:
	rm -f $(programs) simple_vector.o
