programs = \
	grades_mean_homework \
	grades_median_homework \
	quartiles \
	count_words \
	shortest_longest_word_lengths \
	multiple_grades_mean_homework \
	grades_mean_homework_safe \

all: $(programs)

%: %.cpp
	g++ $^ -o $@

clean:
	rm -f $(programs)
