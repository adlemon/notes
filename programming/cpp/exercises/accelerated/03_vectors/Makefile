programs = \
	grades_mean_homework \
	grades_median_homework \

all: $(programs)

%: %.cpp
	g++ $^ -o $@

clean:
	rm -f $(programs)
