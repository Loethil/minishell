/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:17:02 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/15 21:17:03 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (dst[i] && i < size)
		i++;
	while (src[k] && size && i + k < size - 1)
	{
		dst[i + k] = src[k];
		k++;
	}
	if (i < size)
		dst[i + k] = '\0';
	k = 0;
	while (src[k])
		k++;
	return (k + i);
}
