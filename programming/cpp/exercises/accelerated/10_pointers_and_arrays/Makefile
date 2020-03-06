programs = \
	modify_using_pointer \
	print_squares \
	print_letter_grade \
	print_args \
	filter_lines \
	copy_cstring \
	course_letter_grades \
	generic_median \
	string_list \

all: $(programs)

%: %.cpp
	g++ $^ -std=c++14 -o $@

clean:
	rm -f $(programs)
