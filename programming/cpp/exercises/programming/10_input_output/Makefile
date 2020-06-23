PROGRAMS = \
	read_integer \
	write_stats \
	cat2 \
	merge_sorted \

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
