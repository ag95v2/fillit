
/*
**  Return pointer to minimal element of array
*/

int	*ft_min_int(int *arr, int len)
{
	int	*min;

	min = arr;
	while (len--)
	{
		if (*(arr + len) < *min)
			min = arr + len;
	}
	return (min);
}
