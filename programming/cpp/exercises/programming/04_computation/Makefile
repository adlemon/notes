PROGRAMS = \
	char_codes \
	vector_statistics \
	sorted_without_duplicates \
	guess_the_number \
	digit_to_string \
	num_binary_digits \
	prime_numbers \

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
