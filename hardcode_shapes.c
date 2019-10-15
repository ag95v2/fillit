
/*
**	Hardcoded shapes of all figures as positions from topleft corner of 
**	4 * 4 square.
*/

#define T0 {1 - 1, 5 - 1, 6 - 1, 9 - 1}
#define L0 {1 - 1, 2 - 1, 5 - 1, 9 - 1}
#define L1 {1 - 1, 2 - 1, 6 - 1, 10 - 1}
#define SQ {1 - 1, 2 - 1, 5 - 1, 6 - 1}
#define I0 {1 - 1, 2 - 1, 3 - 1, 4 - 1}
#define Z0 {1 - 1, 2 - 1, 6 - 1, 7 - 1}
#define Z1 {2 - 1, 3 - 1, 5 - 1, 6 - 1}

#define ALL_SHAPES {T0, L0, L1, SQ, I0, Z0, Z1}
#define N_SHAPES 7

#include "libft.h"

#define SQ_SIDE 4
#define FIG_SPACE 4

#define	EMPY '.'
#define	FULL '#'

int	isin(int number, int *array, int len)
{
	int	i;
	
	i = 0;
	while (i < len)
	{
		if (array[i] == number)
			return (1);
		i++;
	}
	return (0);
}

void	print_figure(int *start)
{
	int	i;
	
	i = 0;
	while (i < SQ_SIDE * SQ_SIDE)
	{
		ft_putchar(isin(i, start, SQ_SIDE) ? FULL : EMPY);
		if (i % (SQ_SIDE) == SQ_SIDE - 1)
			ft_putchar('\n');
		i++;
	}
}

/*
** Axis can be either 
** 0: horisontal 
** 1: vertical
** 2: "main diagonal"
** In-place operation, array will be modified.
*/
void	reflect_shape(int *shape, int axis)
{
	int i;
	int	row;
	int	col;

	i = 0;
	while (i < FIG_SPACE) 
	{
		col = shape[i] % SQ_SIDE;
		row = shape[i] / SQ_SIDE;
		if (axis == 0)
			shape[i] = (SQ_SIDE - row - 1) * SQ_SIDE + col;
		if (axis == 1)
			shape[i] = shape[i] - col + SQ_SIDE - col - 1;
		if (axis == 2)
			shape[i] = col * SQ_SIDE + row;
		i++;
	}
}

/*
**	In-place rotation of tetramino
**	direction:
**  0 = clockwise;
**  1 = counterclockwise;
*/

void	rotate_shape(int *shape, int direction)
{
	reflect_shape(shape, direction ? 1 : 0);
	reflect_shape(shape, 2);
}

int	main()
{
	int	shapes[N_SHAPES][FIG_SPACE] = ALL_SHAPES;
	int	i;

	i = 0;
	while (i < N_SHAPES)
	{
		ft_putnbr(i);
		ft_putstr(":\n");
		print_figure(shapes[i]);
		ft_putchar('\n');
		rotate_shape(shapes[i], 0);

		print_figure(shapes[i]);
		ft_putchar('\n');
		rotate_shape(shapes[i], 0);

		print_figure(shapes[i]);
		ft_putchar('\n');
		rotate_shape(shapes[i], 0);

		print_figure(shapes[i]);
		ft_putchar('\n');

		i++;
	}
	return (0);
}
