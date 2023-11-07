/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:02:25 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/12 14:02:28 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_ismaj(int c)
{
	if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

int	ft_toupper(int c)
{
	if (ft_isascii(c) == 1)
	{
		if (ft_ismaj(c) == 1)
		{
			c -= 32;
			return (c);
		}
		else if (ft_ismaj(c) == 0)
			return (c);
	}
	return (c);
}
