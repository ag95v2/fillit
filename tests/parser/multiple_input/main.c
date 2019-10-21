
#include "fillit.h"
#include <stdio.h>

void	print_array(int *arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf(i + 1 != len ? "%d, " : "%d\n" , arr[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	shapes[N_SHAPES][2 * FIG_SPACE] = SHAPES; 
	int	*input[MAX_INPUT];
	int	fd;
	int i;
	int	n_tetr;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);

	n_tetr = parse_all(fd, shapes, input);
	if (n_tetr <= 0)
		return(printf("Invalid input\n"));
	i = 0;
	while (i < n_tetr)
	{
		printf("%d: ", i);
		print_array(input[i], 2 * FIG_SPACE);
		i++;
	}

	close(fd);
	return (0);
}
