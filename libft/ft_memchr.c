/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:58:33 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/19 11:58:34 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				r;
	unsigned char		*tab;

	r = -1;
	tab = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (++r < n - 1)
		if (tab[r] == (unsigned char)c)
			return (&tab[r]);
	if (tab[r] == (unsigned char)c)
		return (&tab[r]);
	return (NULL);
}
