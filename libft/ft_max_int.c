
/*
**  Return pointer to maximal element of array
*/

int	*ft_max_int(int *arr, int len)
{
	int	*max;

	max = arr;
	while (len--)
	{
		if (*(arr + len) > *max)
			max = arr + len;
	}
	return (max);
}
