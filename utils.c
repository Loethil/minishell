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
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i])
		return (-1);
	return (0);
}

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(src);
	j = 0;
	while (j < i)
	{
		dst[j] = src[j];
		j++;
	}
	return (dst);
}

char	**ft_find_path(t_dta *dta)
{
	int	i;

	i = 0;
	dta->all_path = ft_split(getenv("PATH"), ':');
	while (dta->all_path[i])
	{
		dta->all_path[i] = ft_freestrjoin(dta->all_path[i], "/");
		i++;
	}
	return (dta->all_path);
}

char	*ft_get_access(t_dta *dta, char *cmd)
{
	int		i;
	char	*tab;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_copystring(cmd));
	while (dta->all_path[i])
	{
		tab = ft_strjoin(dta->all_path[i], cmd);
		if (access(tab, X_OK) == 0)
			return (tab);
		free(tab);
		i++;
	}
	return (NULL);
}

long long	ft_atoll(char *str)
{
	long long	res;
	int			o;
	int			s;

	o = 0;
	res = 0;
	s = 0;
	if (str[o] == '-' )
	{
		o++;
		s++;
	}
	while (str[o] && ft_isdigit(str[o]) == 1)
		res = res * 10 + str[o++] - '0';
	if (s == 1)
		return (-res);
	return (res);
}
