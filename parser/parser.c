
#include "fillit.h"

/*  
** Return a pointer to representation of tetramino if exists else 0.
*/

int	*find_shape(int shapes[N_SHAPES][2 * FIG_SPACE],\
				int current_shape[2 * FIG_SPACE])
{
	int	i;

	i = 0;
	while (i < N_SHAPES)
	{
		if (!ft_memcmp(shapes[i], current_shape, sizeof(int) * 2 * FIG_SPACE))
			return((int *)&shapes[i]);
		i++;
	}
	return (0);
}

int	good_format(char *line)
{
	int	len;

	len = 0;
	while (line[len])
	{
		if (line[len] != FULL && line[len] != EMPTY)
			return (0);
		len++;
	}
	return (len == SQ_SIDE ? 1 : 0);
}

/*
**	Add points to array if any FULL chars are found in line
**  Point is encoded as pair (x,y) where x is number of col, y - number of row
*/

int	add_points(int current_shape[2 * FIG_SPACE], int *n_points, int row, char *line)
{
	int	col;

	col = 0;
	while (line[col])
	{
		if (line[col] == FULL && *n_points == FIG_SPACE)
			return (-1);
		if (line[col] == FULL)
		{
			current_shape[*n_points * 2] = col;
			current_shape[*n_points * 2 + 1] = row;
			*n_points += 1;
		}
		col++;
	}
	return (0);
}

/*
**	We stored only coluumn/row (x/y) coords of tetramino points.
**  Now we need offsets from first position;
*/

void	calculate_offsets(int shape[2 * FIG_SPACE])
{
	int	i;

	i = FIG_SPACE * 2;
	while (i--)
		shape[i] -= shape[(i % 2) ? 1 : 0];
}

/*
**  Read exactly SQ_SIDE lines from fd
**  Check that:
**	-we actually have SQ_SIDE lines in fd
**	-length of each line is == SQ_SIDE
**  -lines contain only allowed chars
**  -exactly FIG_SPACE  *FULL* chars are in tetramino
**  -shape of input tetramino is among allowed shapes
**  Return:
**  0 in case of errors
**  pointer to start of tetramino in case of no errors;
*/

int	*parse_tetr(int fd,\
				int current_shape[2 * FIG_SPACE],\
				int shapes[N_SHAPES][2 * FIG_SPACE])
{
	int		n_points;
	int		n_rows;
	char	*line;
	int		*result;

	n_points = 0;
	n_rows = 0;
	while (n_rows < SQ_SIDE)
	{
		line = 0;
		if (get_next_line(fd, &line) != 1 ||\
			!good_format(line) ||\
			add_points(current_shape, &n_points, n_rows, line) == -1)	
		{
			free(line);
			return (0);
		}
		n_rows++;
		free(line);
	}
	calculate_offsets(current_shape);
	result = find_shape(shapes, current_shape);
	return (n_points != FIG_SPACE || !result ? 0 : result);
}

/*
**  Tetraminos should be separated by exactly one empty line.
**	Return number of tetraminos read or -1 in case of errors.
*/

int	parse_all(	
				int fd,\
				int shapes[N_SHAPES][2 * FIG_SPACE],\
				int	*input[MAX_INPUT + 1]
			 )
{
	int		current_shape[2 * FIG_SPACE];
	int		n_input;
	char	*line;
	int		ret_code;
	int		l;

	n_input = 0;
	while (n_input < MAX_INPUT)
	{
		if (!(input[n_input++] = parse_tetr(fd, current_shape, shapes)))
			return (-1);
		input[n_input] = 0;
		ret_code = get_next_line(fd, &line);
		if (ret_code == -1)
			return (-1);
		if (ret_code == 0)
			return (n_input);
		l = ft_strlen(line);
		free(line);
		if (l > 0 || n_input == MAX_INPUT)
			return (-1);
	}
	return (n_input);
}
