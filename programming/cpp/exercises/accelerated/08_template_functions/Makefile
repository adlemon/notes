programs = \
	median \
	max \
	find \
	copy \
	replace \
	reverse \
	binary_search \
	split \
	compare_course_grade_methods \
	library_templates \
	generate_sentences_iterators \
	map_copy \
	generate_index_iterators \

all: $(programs)

%: %.cpp
	g++ $^ --std=c++14 -o $@

clean:
	rm -f $(programs)
