programs = \
	find_urls \
	compare_grading_methods \
	partition_students_two_pass \
	partition_students_one_pass \
	frame_hcat_iterators \
	copy_vector_bug \
	copy_vector \
	compare_grading_methods_analysis_functions \
	filter_students \
	concatenate_string_vector \

all: $(programs)

%: %.cpp
	g++ $^ -std=c++11 -o $@

clean:
	rm -f $(programs)
