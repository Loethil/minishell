/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:41:00 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/09 15:41:02 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i])
		return (-1);
	return (0);
}

char	*ft_copystring(char *env)
{
	int	i;
	char	*tab;

	i = -1;
	tab = malloc(ft_strlen(env)  * sizeof(char));
	while (env[++i])
		tab[i] = env[i];
	return (tab);
}

// gerer les cas ou nbr est plus grands qu'un long long
long long	ft_atoll(const char *str)
{
	long long	res;
	int	o;
	int	s;

	o = 0;
	res = 0;
	s = 0;
	if (str[o] == '-' )
	{
		o++;
		s++;
	}
	while (str[o] && (ft_isdigit(str[o]) == 1))
		res = res * 10 + str[o++] - '0';
	if (s == 1)
	 	return (-res);
	return (res);
}
