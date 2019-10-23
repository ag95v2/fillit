
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

/*
**  We can arrange any configuration in field 15*15
**	Proof:
**	lemma 1: In field of size 5*5 we can place any 3 tetraminos
**	proof lemma1: 
**				Obvious. 
**	Q.E.D.
**	Now split 27 input tetraminos into 9 groups of 3 tetranios and use lemma 1.
**	Q.E.D.
*/
# define	MAX_FIELD 15

int	*parse_tetr(int fd,\
				int current_shape[2 * FIG_SPACE],\
				int shapes[N_SHAPES][2 * FIG_SPACE]);

int	parse_all(	
				int fd,\
				int shapes[N_SHAPES][2 * FIG_SPACE],\
				int	*input[MAX_INPUT + 1];
			 );
int	solver(int *input[MAX_INPUT], int n_tetr);

#endif
