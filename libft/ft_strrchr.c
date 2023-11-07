/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:46:37 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/12 15:46:38 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (s[i] == (char) c)
		return ((char *)&s[i]);
	while (i-- >= 0)
		if (s[i] == (char) c)
			return ((char *)&s[i]);
	return (NULL);
}
