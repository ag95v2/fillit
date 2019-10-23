
HARDCODE = "encoder/hardcode_shapes"
MACRO_NAME = "SHAPES"
NAME = fillit

all: generate_shapes_header
	gcc -g -Wall -Wextra -Werror -c -o main.o main.c -I libft/includes -L libft -lft -I inc/
	gcc -g -Wall -Wextra -Werror -c -o parser.o parser/parser.c -I libft/includes -L libft -lft -I inc/
	gcc -g -Wall -Wextra -Werror -c -o solver.o solver/solver.c -I libft/includes -L libft -lft -I inc/
	gcc -g -Wall -Wextra -Werror -o $(NAME) main.o parser.o solver.o -L libft -lft


generate_shapes_header:
	gcc -g -Wall -Wextra -Werror $(HARDCODE).c -I libft/includes -L libft -lft -o $(HARDCODE)
	cat encoder/first_part_header > inc/shapes.h
	echo -n "# define $(MACRO_NAME) " >> inc/shapes.h
	./$(HARDCODE) >> inc/shapes.h
	cat encoder/last_part_header >> inc/shapes.h

debug_encoder:
	gcc -g -Wall -Wextra -Werror $(HARDCODE).c -I libft/includes -L libft -lft -o $(HARDCODE) -DDEBUG
	./$(HARDCODE)
