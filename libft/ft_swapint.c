
/*
**  Similar as ft_swap. Probably, faster.
*/

void	ft_swapint(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
