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

char	*ft_copystring(char *str)
{
	int		i;
	char	*tab;

	i = 0;
	tab = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		tab[i] = str[i];
		i++;
	}
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
		dta->newenv[i] = env[i];
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

int	ft_pwdorenv(t_dta *dta, char **newenv, char *tab)
{
	int	i;

	if (ft_strncmp(tab, "PWD", 3) == 0)
	{
		i = ft_findpwd(newenv);
		if (i == -1)
			return (-1);
		printf("%s\n", newenv[i] + 4);
		dta->res = 0;
		return (0);
	}
	if (ft_strncmp(tab, "ENV", 3) == 0)
	{
		i = 0;
		while (newenv[i])
			printf("%s\n", newenv[i++]);
		dta->res = 0;
		return (0);
	}
	return (-1);
}
