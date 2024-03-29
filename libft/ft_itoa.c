/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:26:03 by bgian             #+#    #+#             */
/*   Updated: 2019/09/25 18:18:54 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			str_rev(char *s)
{
	int		len;
	int		i;
	char	tmp;

	i = 0;
	len = ft_strlen(s);
	while (i < (len - i - 1))
	{
		tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
		i++;
	}
}

static int			my_abs(int n)
{
	return (n > 0 ? n : -1 * n);
}

char				*ft_itoa(int n)
{
	char	*s;
	int		i;

	i = 0;
	s = ft_memalloc(12);
	if (!s)
		return (0);
	if (n < 0)
	{
		s[0] = '-';
		i++;
	}
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		s[i++] = my_abs(n % 10) + '0';
		n = n / 10;
	}
	str_rev((s[0] == '-') ? s + 1 : s);
	return (s);
}
