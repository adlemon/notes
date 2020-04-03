programs = \
	simple_string \
	managed_string \

all: $(programs)

%: %.cpp
	g++ -std=c++14 $^ -o $@

clean:
	rm -f $(programs)
