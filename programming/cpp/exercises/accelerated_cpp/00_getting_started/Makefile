programs = \
	hello_world \
	escape_characters \
	print_tabs \
	print_hello_world_program \
	hello_world_newlines \

all: $(programs)

%: %.cpp
	g++ $^ -o $@

clean:
	rm -f $(programs)
