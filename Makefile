
HARDCODE = "hardcode_shapes"


all:
	gcc -g -Wall -Wextra -Werror $(HARDCODE).c -I libft/includes -L libft -lft -o $(HARDCODE) -DDEBUG
