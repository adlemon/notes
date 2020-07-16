PROGRAMS = \
	to_from_string \
	get_io \
	regex_search \
	regex_match \
	line_matches \

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
