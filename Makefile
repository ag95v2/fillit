
HARDCODE = "encoder/hardcode_shapes"
MACRO_NAME = "SHAPES"

all: generate_shapes_header

generate_shapes_header:
	gcc -g -Wall -Wextra -Werror $(HARDCODE).c -I libft/includes -L libft -lft -o $(HARDCODE)
	cat encoder/first_part_header > inc/shapes.h
	echo -n "# define $(MACRO_NAME) " >> inc/shapes.h
	./$(HARDCODE) >> inc/shapes.h
	cat encoder/last_part_header >> inc/shapes.h

debug_encoder:
	gcc -g -Wall -Wextra -Werror $(HARDCODE).c -I libft/includes -L libft -lft -o $(HARDCODE) -DDEBUG
	./$(HARDCODE)
