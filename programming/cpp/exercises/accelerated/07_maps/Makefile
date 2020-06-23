programs = \
	count_words \
	make_index \
	generate_sentences \
	count_words_sorted \
	letter_grade_histogram \
	make_index_deduplicate \
	make_index_wrap \
	generate_sentences_list \
	generate_sentences_iterative \
	generate_index_line_vs_lines \
	index_urls \
	nrand_binary \
	nrand_limited \

all: $(programs)

%: %.cpp
	g++ $^ --std=c++14 -o $@

clean:
	rm -f $(programs)
