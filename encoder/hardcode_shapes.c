
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


#define SQ_SIDE 4
#define FIG_SPACE 4
#define N_ROTATIONS 4	

#define	EMPY '.'
#define	FULL '#'

#include "libft.h"

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

/*
**	For debug only. Figure is stored in deprecated 1-d coordinates.
**  Cool guys now use 2-d coords.
*/

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
** Function uses 1-d coords. Be careful.
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
**  1-d coords are used here.
*/

void	rotate_shape(int *shape, int direction)
{
	reflect_shape(shape, direction ? 1 : 0);
	reflect_shape(shape, 2);
}

/*
**  Now it seems more convinient to store 2 coordinates of shape
**  instead of one. We need to perform these transformations.
**  First coordinate will be x(column) offset, second - y(row) offset
**  (Offset from topleft position)
*/

int		*change_coord(int *shape)
{
	int	*xy_offsets;
	int	i;

	xy_offsets = (int *)malloc(sizeof(int) * FIG_SPACE * 2);
	while (i < FIG_SPACE)
	{
		xy_offsets[2 * i] = shape[i] % SQ_SIDE;
		xy_offsets[2 * i + 1] = shape[i] / SQ_SIDE;
		i++;
	}
	#ifdef DEBUG
	//ft_print_array(xy_offsets, FIG_SPACE * 2);
	#endif
	i *= 2;
	while (i--)
		xy_offsets[i] -= xy_offsets[(i % 2) ? 1 : 0];
	return (xy_offsets);
}


void	print_shape_debug(int *shape)
{
	int	i;
	int	*xy_offsets;

	i = 0;
	while (i++ < N_ROTATIONS)
	{
		ft_putstr("\n");
		print_figure(shape);
		ft_bsort_int(shape, FIG_SPACE, 1);
		ft_print_array(shape, FIG_SPACE);
		ft_putchar('\n');
		xy_offsets = change_coord(shape);
		ft_print_array(xy_offsets, FIG_SPACE * 2);
		free(xy_offsets);
		ft_putchar('\n');
		rotate_shape(shape, 0);
	}
}

int		is_unique(int *shape_2d, t_list *seen)
{
	while (seen)
	{
		if (!ft_memcmp(shape_2d, seen->content, FIG_SPACE * 2 * sizeof(int)))
			return (0);
		seen = seen->next;
	}
	return (1);
}

/*
**  Perform all possible rotations of shapes in sorted 1-d coords
**  Change coords to 2-d.
**  Drop duplicates.
**  Store result in list of arrays.
*/

t_list	*get_all_unique(int shapes[N_SHAPES][FIG_SPACE])
{
	int		i;
	int		j;
	t_list	*res;
	t_list	*new;

	i = -1;
	res = 0;
	while (++i < N_SHAPES)
	{
		j = -1;
		while (++j < N_ROTATIONS)
		{
			ft_bsort_int(shapes[i], FIG_SPACE, 1);
			new = ft_lstnew(change_coord(shapes[i]), FIG_SPACE * 2);
			if (is_unique(new->content, res))
				ft_lstadd(&res, new);
			rotate_shape(shapes[i], 1);
		}
	}
	return (res);
}

void	print_2d_shape(int *xy_offsets)
{
	int	i;

	i = 0;
	ft_putchar('{');
	while (i < FIG_SPACE * 2)
	{
		ft_putnbr(xy_offsets[i]);
		ft_putstr(i == FIG_SPACE * 2 - 1? "" :", ");
		i++;
	}
	ft_putstr("}");
}

void	print_all_shapes(t_list *all_shapes)
{
	int	i;

	i = 0;
	ft_putstr("{");
	while (all_shapes)
	{
		i++;
		print_2d_shape(all_shapes->content);
		ft_putstr(all_shapes->next ? ", " : "");
		all_shapes = all_shapes->next;
	}
	ft_putstr("}\n");
	ft_putstr("# define N_SHAPES ");
	ft_putnbr(i);
	ft_putstr("\n");
	#ifdef DEBUG
	ft_putstr("Total: ");
	ft_putnbr(i);
	ft_putstr("\n");
	#endif
}

void	print_nice_format(int shapes[N_SHAPES][FIG_SPACE])
{
	t_list	*all_unique_2d;

	all_unique_2d = get_all_unique(shapes);
	#ifdef DEBUG
	ft_putstr("Printing all shapes\n");
	#endif
	print_all_shapes(all_unique_2d);
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
	ft_putstr("Now nice format: \n");
	#endif
	print_nice_format(shapes);
	return (0);
}
