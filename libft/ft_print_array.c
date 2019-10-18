#include "libft.h"

/*
**  Just print an integer aray
*/

void	ft_print_array(int *a, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_putnbr(a[i]);
		ft_putstr(i < len - 1? ", " : "\n");
		i++;
	}
}
