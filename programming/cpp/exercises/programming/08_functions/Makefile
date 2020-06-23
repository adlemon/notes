PROGRAMS = \
	order_of_destructors \
	namespaces \
	static_function_variables \
	fibonacci \
	reverse_vector \
	vector_stats \

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
