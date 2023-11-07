/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:58:41 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/19 11:58:43 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			r;
	unsigned char	*tab1;
	unsigned char	*tab2;

	r = 0;
	tab1 = (unsigned char *) s1;
	tab2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (r < n)
	{
		if (tab1[r] != tab2[r])
			return (tab1[r] - tab2[r]);
		r++;
	}
	return (0);
}
