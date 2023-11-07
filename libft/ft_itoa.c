/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:03:57 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/19 19:04:00 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	mallocint(int c)
{
	int	r;

	r = 1;
	if (c < 0)
	{
		r++;
		c = -c;
	}
	while (c >= 10)
	{
		c = c / 10;
		r++;
	}
	return (r);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	char			*tab;
	int				a;

	if (n < -2147483647)
		return (ft_strdup("-2147483648"));
	a = mallocint(n);
	tab = (char *) malloc((mallocint(n) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	nbr = n;
	tab[a--] = '\0';
	if (n == 0)
		tab[0] = '0';
	if (n < 0)
	{
		tab[0] = '-';
		nbr = -n;
	}
	while (nbr != 0)
	{
		tab[a--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (tab);
}
