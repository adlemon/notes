PROGRAMS = \
	managed_picture_test \

FLAGS = \
	-std=c++17 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-pedantic-errors \

all: $(PROGRAMS)

managed_pointer.o: managed_pointer.cpp
	g++ $(FLAGS) -c managed_pointer.cpp -o managed_pointer.o

managed_picture.o: managed_picture.cpp managed_pointer.cpp
	g++ $(FLAGS) -c managed_picture.cpp

%: %.cpp managed_pointer.cpp managed_picture.cpp
	g++ $(FLAGS) $@.cpp -o $@

clean:
	rm -f \
		managed_pointer.o \
		managed_picture.o \
		$(PROGRAMS)
