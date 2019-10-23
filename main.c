
#include <fillit.h>

int	main(int argc, char **argv)
{
	int	*input[MAX_INPUT + 1];
	int	shapes[N_SHAPES][2 * FIG_SPACE] = SHAPES;
	int	n_tetr;
	int	fd;

	if (argc != 2)
	{
		ft_putstr("Missing argument\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	n_tetr = parse_all(fd, shapes, input);
	if (n_tetr <= 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	solver(input, n_tetr);
	return (0);
}
