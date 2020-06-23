PROGRAMS = \
	decimal_octal_hexadecimal \
	print_floating_point \
	append_to_file \
	read_write_position \
	string_streams \
	character_types \
	change_case \
	word_histogram \
	lines_with_word \

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
