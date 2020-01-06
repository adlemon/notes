programs = \
	greet_padded \
	greet_unpadded \
	greet_padded_2d \
	greet_padded_user_specified \
	greet_padded_spaces_string \
	print_shapes \
	count_10_to_minus5 \
	product_1_9 \
	compute_maximum \

all: $(programs)

%: %.cpp
	g++ $^ -o $@

clean:
	rm -f $(programs)
