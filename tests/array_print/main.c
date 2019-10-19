
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

int main()
{
	int	shapes[N_SHAPES][2 * FIG_SPACE] = SHAPES;
	int	i;

	i = 0;
	while (i < N_SHAPES)
		print_shape(shapes[i++]);
	
	return (0);
}
