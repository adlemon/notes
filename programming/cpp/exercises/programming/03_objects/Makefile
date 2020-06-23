PROGRAMS = \
	integer_arithmetic \
	sort_three_integers \
	odd_or_even \
	double_arithmetic \
	total_coins_value \

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
