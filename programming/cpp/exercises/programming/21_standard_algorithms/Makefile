PROGRAMS = \
	stl_algorithms \
	associative_containers \
	stream_iterators \
	pointer_set \
	word_histogram \

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
