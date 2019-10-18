
/*
**  Maximal value of integer array
*/


int	ft_maxval_int(int *a, unsigned int len)
{
	int	max;

	max = a[len - 1];
	while (len--)
	{
		if (a[len] > max)
			max = a[len];
	}
	return (max);
}
