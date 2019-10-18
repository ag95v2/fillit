
#include "libft.h"

/*
**	Subtract a number from integer array
**  If in_place, modify existing object else create new
*/

int	*ft_array_subtract(int *arr, unsigned int len, int number, int in_place)
{
	int				*res;
	unsigned int	i;

	res = in_place ? arr : (int *)malloc(sizeof(int) * len);
	if (!res)
		return (0);
	i = 0;
	while (i < len)
	{
		res[i] = arr[i] - number;
		i++;
	}
	return (res);
}

