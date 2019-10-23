
#include "fillit.h"
#include <stdio.h>

void	print_shape(int *shape)
{
	int	i;

	i = 0;
	while (i < 2 * FIG_SPACE -1 )
	{
		printf("%d, ", shape[i]);
		i++;
	}
	printf("%d\n", shape[i]);
}


void	print_field(char field[MAX_FIELD][MAX_FIELD], int sq_side)
{
	int	col;
	int	row;

	row = 0;
	while (row < sq_side)
	{
		col = 0;
		while (col < sq_side)
			ft_putchar(field[col++][row]);
		ft_putchar('\n');
		row++;
	}
}

void	init_field(char field[MAX_FIELD][MAX_FIELD])
{
	int	i;
	int	j;

	i = -1;
	while (++i < MAX_FIELD)
	{
		j = 0;
		while (j < MAX_FIELD)
			field[i][j++] = EMPTY;
	}
}

int		can_insert(
					char field[MAX_FIELD][MAX_FIELD], 
					int *shape, 
					int x, 
					int y,
					int	sq_side
					)
{
	int	i;
	int	row;
	int	col;

	i = 0;
	while (i < FIG_SPACE)
	{
		col = x + shape[2 * i];
		row = y + shape[2 * i + 1];
		if (
				col < 0 ||\
				col >= sq_side ||\
				row < 0 ||\
				row >= sq_side ||\
				field[col][row] != EMPTY)
			return (0);
		i++;
	}
	return (1);
}

int		insert(
					char field[MAX_FIELD][MAX_FIELD], 
					int *shape, 
					int x, 
					int y,
					char symbol
				)
{
	int	i;
	int	row;
	int	col;

	i = 0;
	while (i < FIG_SPACE)
	{
		col = x + shape[2 * i];
		row = y + shape[2 * i + 1];
		field[col][row] = symbol;
		i++;
	}
	return (0);
}

int	*random_tetramino(int shapes[N_SHAPES][2 * FIG_SPACE])
{
	int random_shape = rand() % N_SHAPES;

	return ((int *)&shapes[random_shape]);
}

/*
**	Return number of possible places where we can insert a tetramino 
*/

int	fill_insertable_positions(\
							int *shape, \
							char field[MAX_FIELD][MAX_FIELD],\
							int	*positions\
							)
{
	int	row;
	int	col;
	int	n_pos;

	n_pos = 0;
	row = 0;
	while (row < SQ_SIDE)
	{
		col = 0;
		while (col < SQ_SIDE)
		{
			if (can_insert(field, shape, col, row, SQ_SIDE))
			{
				positions[n_pos * 2] = col;
				positions[n_pos * 2 + 1] = row;
				n_pos++;
			}
			col++;
		}
		row++;
	}
	return (n_pos);
}

void	insert_into_random_position(\
								char field[MAX_FIELD][MAX_FIELD], \
								int *shape,\
								int	*positions,\
								int	n_pos
								)
{
	int random_pos = rand() % (n_pos - 1);

	insert(\
			field,\
			shape, \
			positions[2 * random_pos], \
			positions[2 * random_pos + 1], \
			FULL);
}

void	print_random_shape(\
		int			shapes[N_SHAPES][2 * FIG_SPACE],\
		char		field[MAX_FIELD][MAX_FIELD],\
		int			positions[SQ_SIDE * SQ_SIDE * 2]\
		)
{
	int			n_pos;
	int			*shape;

	init_field(field);
	shape = random_tetramino(shapes);
	n_pos = fill_insertable_positions(shape, field, positions);
	insert_into_random_position(field, shape, positions, n_pos);
	print_field(field, SQ_SIDE);
}

/*
**  Pass a number of tetraminos as argument.
**  Program inserts random tetraminos into random positions 
**  and prints field to stdout
*/

/*
**	Random seed is not used this time.
*/
#define RANDOM_SEED 69

#include <time.h> 
int main(int argc, char **argv)
{
	int			shapes[N_SHAPES][2 * FIG_SPACE] = SHAPES;
	char		field[MAX_FIELD][MAX_FIELD];
	int			positions[SQ_SIDE * SQ_SIDE * 2];
	int			n_tetr;

	if (argc != 2)
	{
		printf("Usage: ./generator N_tetraminos\n");
		return (0);
	}

	n_tetr = ft_atoi(argv[1]);
	srand(time(NULL));

	while (n_tetr--)
	{
		print_random_shape(shapes, field, positions);
		n_tetr ? ft_putstr("\n") : ft_putstr("");
	}

	return (0);
}
