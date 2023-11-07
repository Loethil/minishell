/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:05:46 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/17 11:05:47 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	is_charset(char c, const char *charset)
{
	int	r;

	r = 0;
	while (charset[r])
		if (charset[r++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		a;
	int		v;
	int		e;
	char	*tab;

	a = 0;
	while (s1[a] && is_charset(s1[a], set) == 1)
		a++;
	v = ft_strlen(s1);
	while (v > a && is_charset(s1[v - 1], set) == 1)
		v--;
	e = ft_strlen(s1) - v;
	tab = malloc((ft_strlen(s1) - e - a + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	e = 0;
	while (a < v)
		tab[e++] = s1[a++];
	tab[e] = 0;
	return (tab);
}
