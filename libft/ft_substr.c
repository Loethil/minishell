/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:50:48 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/15 22:50:49 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	r;
	size_t	a;
	char	*tab;

	r = start;
	a = 0;
	if (start >= ft_strlen(s))
	{
		tab = (char *) malloc(sizeof (char));
		tab[0] = '\0';
		return (tab);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	tab = (char *) malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (r < len + start)
	{
		tab[a] = s[r];
		a++;
		r++;
	}
	tab[a] = '\0';
	return (tab);
}
