
#include "libft.h"

#define N 500000000

int	main()
{
	int	a;
	int	b;
	int	i;

	a = 12345;
	b = 43215;
	i = 0;
	#ifdef USE_GENERIC_SWAP
	while (i++ < N)
		ft_swap(&a,	&b, sizeof(int));
	#else

	while (i++ < N)
		ft_swapint(&a, &b);
	#endif
}
