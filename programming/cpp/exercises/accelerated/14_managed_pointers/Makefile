PROGRAMS = \
	managed_pointer_example \
	course_grades_managed_pointer \
	managed_pointer_string \
	managed_pointer_counter \

FLAGS = \
	-std=c++17 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-pedantic-errors \

all: $(PROGRAMS)

managed_pointer.o: managed_pointer.cpp
	g++ $(FLAGS) -c managed_pointer.cpp

%: %.cpp managed_pointer.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f managed_pointer.o $(PROGRAMS)
