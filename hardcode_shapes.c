
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
#define N_ROTATIONS 4	

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

void	print_shape_debug(int *shape)
{
	int	i;
	int	*new;

	i = 0;
	while (i++ < N_ROTATIONS)
	{
		ft_putstr("\n");
		print_figure(shape);
		ft_bsort_int(shape, FIG_SPACE, 1);
		new = ft_array_subtract(shape, FIG_SPACE, \
				ft_minval_int(shape, FIG_SPACE), 0);
		ft_print_array(new, FIG_SPACE);
		free(new);
		ft_putchar('\n');
		rotate_shape(shape, 0);
	}
}

/*
**	Print nonzero elements separated by commas, enclosed with curly brackets
*/
void	print_macro_shape(int *shape)
{
	int	i;

	i = 0;
	ft_putchar('{');
	while (i < FIG_SPACE)
	{
		if (shape[i])
		{
			ft_putnbr(shape[i]);
			ft_putstr(FIG_SPACE - i == 1 ? "}" : ", ");
		}
		i++;
	}
}

/* Some shapes are rotation invariant. We need a single instance of each*/
int		is_duplicate(int *shape, t_list *unique_shapes)
{
	while (unique_shapes)
	{
		if (ft_memcmp(shape, unique_shapes->content, FIG_SPACE) == 0)
			return (1);
		unique_shapes = unique_shapes->next;
	}
	return (0);
}

/* 
**  Rotate each shepe 4 times. Drop duplicates.
**  Return a list with unique shapes 
*/
t_list	*get_unique_shapes(int shapes[N_SHAPES][FIG_SPACE])
{
	int		i;
	int		j;
	int		*offsets;
	t_list	*res;
	t_list	*new;
	int		total;

	total = 0;
	res = 0;
	i = 0;
	while (i < N_SHAPES)
	{
		j = 0;
		while (j++ < N_ROTATIONS)
		{
			ft_bsort_int(shapes[i], FIG_SPACE, 1);
			offsets = ft_array_subtract(shapes[i], FIG_SPACE, \
					ft_minval_int(shapes[i], FIG_SPACE), 0);
			new = ft_lstnew(offsets, FIG_SPACE);
			if (!is_duplicate(shapes[i], res))
			{
				total++;
				ft_lstadd(&res, new);
			}
			rotate_shape(shapes[i], 0);
		}
		i++;
	}
	ft_putstr("Total: ");
	ft_putnbr(total);
	ft_putchar('\n');
	return (res);
}

void	print_unique_shapes(t_list *unique_shapes)
{
	ft_putstr("{");
	while (unique_shapes->next)
	{
		print_macro_shape(unique_shapes->content);
		ft_putstr(", ");
		unique_shapes = unique_shapes->next;
	}
	print_macro_shape(unique_shapes->content);
	ft_putstr("}");
}

void	print_macro_array(int shapes[N_SHAPES][FIG_SPACE])
{
	t_list	*unique_shapes;

	unique_shapes = get_unique_shapes(shapes);
	print_unique_shapes(unique_shapes);
	ft_lstdel(&unique_shapes, &del_simple);
}

int	main()
{
	int	shapes[N_SHAPES][FIG_SPACE] = ALL_SHAPES;
	#ifdef DEBUG
	int	i;

	i = 0;
	while (i < N_SHAPES)
	{
		ft_putnbr(i);
		print_shape_debug(shapes[i]);
		i++;
	}
	#endif
	print_macro_array(shapes);
	ft_putchar('\n');
	return (0);
}
