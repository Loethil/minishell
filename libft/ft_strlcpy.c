/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:24:29 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/11 15:24:30 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(src);
	j = -1;
	if (i + 1 < size)
	{
		while (++j < i + 1)
			dst[j] = src[j];
	}
	else if (size > 0)
	{
		while (++j < size - 1)
			dst[j] = src[j];
		dst[j] = 0;
	}
	return (i);
}
