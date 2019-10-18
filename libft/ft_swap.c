
#include "libft.h"

/*
** Swap 2 non-overlapping objects
*/

void	ft_swap(void *a, void *b, size_t len)
{
	char	tmp;

	while (len--)
	{
		tmp = *(char *)a;
		*(char *)a = *(char *)b;
		*(char *)b = tmp;
	}
}
