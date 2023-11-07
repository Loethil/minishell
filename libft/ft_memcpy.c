/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:44:44 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/11 14:44:45 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tab1;
	unsigned char	*tab2;

	if (!src && !dest)
		return (0);
	i = 0;
	tab1 = (unsigned char *)src;
	tab2 = (unsigned char *)dest;
	while (i < n)
	{
		tab2[i] = tab1[i];
		i++;
	}
	return (dest);
}
