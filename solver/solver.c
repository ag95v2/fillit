
#include "fillit.h"

/*
**	Pre-calculate starting side of square that we are going to fill
*/

int		start_sq_side(int n_tetr)
{
	int	i;

	i = 0;
	while (i * i < n_tetr * FIG_SPACE)
		i++;
	return (i * i == n_tetr * FIG_SPACE ? i : i + 1);
}

/*
**  First index is col, second - row.
*/

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

/*
**  First index is col, second - row.
*/

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

/*
**  Return 1 if we can insert a shape into field
**	at position (x,y) (col, row) else 0.
**  If shape goes beyond the field, also return 0
**  Remember that first index of field is row as that convention might look 
**  somewhat counter-intuitive.
*/

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

/*
**	Check if tetraminos can be packed inside a field with side sq_side
**  return 0 in case of success
**  Side effects: field is filled with corresponding letters of alphabet
**  In case of failure, field is cleaned-up
*/

int	check_size(
		char field[MAX_FIELD][MAX_FIELD],\
		int *input[MAX_INPUT],\
		int n_tetr,\
		int sq_side)
{
	int			col;
	int			row;
	static char	symbol;

	if (!n_tetr)
		return (0);
	row = -1;
	while (++row < sq_side)
	{
		col = -1;
		while (++col < sq_side)
		{
			if (can_insert(field, *input, col, row, sq_side))
			{
				insert(field, *input, col, row, symbol++ + 'A');
				if (check_size(field, input + 1, n_tetr - 1, sq_side))
				{
					symbol--;
					insert(field, *input, col, row, EMPTY);
				}
				else
					return (0);
			}
		}
	}
	return (1);
}

int	solver(int *input[MAX_INPUT], int n_tetr)
{
	static char	field[MAX_FIELD][MAX_FIELD];
	int			sq_side;

	init_field(field);
	sq_side = start_sq_side(n_tetr);
	while (check_size(field, input, n_tetr, sq_side))
		sq_side++;
	print_field(field, sq_side);
	return (sq_side);
}
