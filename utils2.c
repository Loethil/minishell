/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:18:56 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/02 15:18:58 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_copystring(char *env)
{
	int		i;
	char	*tab;

	i = -1;
	tab = malloc(ft_strlen(env) * sizeof(char));
	while (env[++i])
		tab[i] = env[i];
	return (tab);
}

char	**changeenv(t_dta *dta, char **env)
{
	int	i;

	i = 0;
	dta->newenv = malloc((ft_tablen(env) + 1) * sizeof(char *));
	while (env[i])
	{
		dta->newenv[i] = ft_copystring(env[i]);
		i++;
	}
	return (dta->newenv);
}

int	ft_findpwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PWD=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}
