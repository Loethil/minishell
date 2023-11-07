/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:18:57 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/20 16:19:02 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	r;
	char			*tab;

	if (!s || !f)
		return (NULL);
	tab = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	r = 0;
	while (s[r])
	{
		tab[r] = f(r, s[r]);
		r++;
	}
	tab[r] = '\0';
	return (tab);
}
