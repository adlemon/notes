programs = \
	failing_students_vector \
	failing_students_list \
	split_string \
	frame_picture \
	permuted_index \
	filter_list_vector_performance_comparison \
	failing_students_typedef \
	frame_centered \
	failing_students_resize \
	hcat_append \
	all_lowercase_some_uppercase \
	print_palindromes \
	ascenders_descenders \

all: $(programs)

%: %.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -f $(programs)
