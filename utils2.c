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

char	*ft_copystring(char *env)
{
	int		i;
	char	*tab;

	i = -1;
	tab = ft_calloc((ft_strlen(env) + 1), sizeof(char));
	while (env[++i])
		tab[i] = env[i];
	tab[i] = '\0';
	return (tab);
}

char	**changeenv(t_dta *dta, char **env)
{
	int	i;

	i = 0;
	dta->newenv = ft_calloc((ft_explen(env) + 1), sizeof(char *));
	while (env[i])
	{
		dta->newenv[i] = ft_copystring(env[i]);
		i++;
	}
	dta->newenv[i] = NULL;
	return (dta->newenv);
}

int	ft_findpwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_pwdorenv(char **newenv, char *tab)
{
	int	i;

	if (ft_strncmp(tab, "PWD", 3) == 0)
	{
		i = ft_findpwd(newenv);
		printf("%s\n", newenv[i] + 4);
	}
	if (ft_strncmp(tab, "ENV", 3) == 0)
	{
		i = 0;
		while (newenv[i])
			printf("%s\n", newenv[i++]);
	}
}
