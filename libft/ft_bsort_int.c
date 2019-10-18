#include "libft.h"

/*
**	Sort any type of array according to function int cmp(a, b)
**  If a > b return positive number;
*/

static void put_min_first(int *a, unsigned int len)
{
	ft_swapint(ft_min_int(a, len), a);
}

static void put_max_first(int *a, unsigned int len)
{
	ft_swapint(ft_max_int(a, len), a);
}

/*
**	Sort integer array in-place
*/
void		ft_bsort_int(int *a, unsigned int len, int ascending)
{
	while (len)
	{
		ascending ? put_min_first(a, len) : put_max_first(a, len);
		len--;
		a++;
	}
}
