/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:11:08 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/11 15:11:09 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tab1;
	unsigned char	*tab2;

	if (!dest && !src)
		return (NULL);
	tab1 = (unsigned char *)src;
	tab2 = (unsigned char *)dest;
	if (tab2 > tab1)
	{
		while (n--)
			tab2[n] = tab1[n];
	}
	else
	{
		i = -1;
		while (++i < n)
			tab2[i] = tab1[i];
	}
	return (dest);
}
