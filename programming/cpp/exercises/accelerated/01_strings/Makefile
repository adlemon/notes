programs = \
	greet \
	greet_framed \

all: $(programs)

%: %.cpp
	g++ $^ -o $@

clean:
	rm -f $(programs)
