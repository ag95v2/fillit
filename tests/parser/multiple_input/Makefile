
PROJECT_PATH = "../../../"
USED_LIBS = -L$(PROJECT_PATH)/libft -lft

all:
	gcc -g -Wall -Wextra -Werror -c -o parser.o $(PROJECT_PATH)parser/parser.c -I $(PROJECT_PATH)inc/ -I $(PROJECT_PATH)libft/includes $(USED_LIBS)
	gcc -g -Wall -Wextra -Werror -c -o main.o main.c -I $(PROJECT_PATH)inc/ -I $(PROJECT_PATH)libft/includes $(USED_LIBS)
	gcc -g -Wall -Wextra -Werror -o test_parser main.o parser.o $(USED_LIBS)
