
#include "libft.h"

void	print_array(int *a, int len)
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

int	main()
{
	int	a[] = {1, 2, 3, 4, 5};
	int b[] = {0, 4, 5, 8};

	print_array(a, 5);
	ft_bsort_int(a, 5, 0);
	print_array(a, 5);
	ft_bsort_int(a, 5, 1);
	print_array(a, 5);
	ft_bsort_int(b, 4, 1);
	print_array(b, 4);
	return (0);
}
