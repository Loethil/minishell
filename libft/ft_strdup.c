/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:38:10 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/15 22:38:11 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tab;
	int		i;

	i = 0;
	tab = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
