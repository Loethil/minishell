/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:42:43 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/20 18:42:44 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	countword(char const *s, char c)
{
	int	r;
	int	a;

	r = 0;
	a = 0;
	while (s[r])
	{
		while (s[r] == c)
			r++;
		if (s[r] && s[r] != c)
		{
			a++;
			while (s[r] && s[r] != c)
				r++;
		}
	}
	return (a + 1);
}

char	*theword(int *v, const char *s, char c)
{
	int		n;
	int		o;
	char	*tub;

	n = 0;
	o = 0;
	while (s[*v] == c)
		(*v)++;
	while (s[*v + n] && s[*v + n] != c)
		n++;
	tub = malloc((n + 1) * sizeof(char));
	if (!tub)
		return (NULL);
	while (o < n)
		tub[o++] = s[(*v)++];
	tub[o] = '\0';
	return (tub);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		v;
	int		e;

	v = 0;
	e = 0;
	if (!s)
		return (NULL);
	tab = malloc(countword(s, c) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (e < countword(s, c) - 1)
		tab[e++] = theword(&v, s, c);
	tab[e] = NULL;
	return (tab);
}
