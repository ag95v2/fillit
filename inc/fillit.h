
#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include "shapes.h"
# include <fcntl.h>

# define FIG_SPACE 4
# define MAX_INPUT 26
# define BUFFSIZE MAX_INPUT * (SQ_SIDE * (SQ_SIDE + 1) + 1)
# define SQ_SIDE 4

# define	EMPTY '.'
# define	FULL '#'

int	*parse_tetr(int fd,\
				int current_shape[2 * FIG_SPACE],\
				int shapes[N_SHAPES][2 * FIG_SPACE]);

int	parse_all(	
				int fd,\
				int shapes[N_SHAPES][2 * FIG_SPACE],\
				int	*input[MAX_INPUT + 1];
			 );
#endif
