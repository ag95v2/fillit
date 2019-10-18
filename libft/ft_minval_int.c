
/*
**  Minimal value of integer array
*/


int	ft_minval_int(int *a, unsigned int len)
{
	int	min;

	min = a[len - 1];
	while (len--)
	{
		if (a[len] < min)
			min = a[len];
	}
	return (min);
}
