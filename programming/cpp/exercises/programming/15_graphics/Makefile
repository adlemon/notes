PROGRAMS = \
	exp_taylor_series \

FLAGS = \
	-std=c++17 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-pedantic-errors \

GRAPHICS_FILES = \
	../stroustrup/Graph.cpp \
	../stroustrup/GUI.cpp \
	../stroustrup/Simple_window.cpp \
	../stroustrup/Window.cpp \

FLTK_CONFIG = \
	`fltk-config --ldflags --use-images`

all: $(PROGRAMS)

%: %.cpp
	g++ $^ $(GRAPHICS_FILES) -o $@ $(FLAGS) $(FLTK_CONFIG)

clean:
	rm -f $(PROGRAMS)
