PROGRAMS = \
	type_sizes \
	void_star \
	directions_of_stack_and_heap \
	fixed_size_vector \
	doubly_linked_list \
	this_pointer \

FLAGS = \
	-std=c++17 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-pedantic-errors \

all: $(PROGRAMS)

%: %.cpp
	g++ $^ -o $@ $(FLAGS)

clean:
	rm -f $(PROGRAMS)
