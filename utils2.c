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
	int	i;
	char	*tab;

	i = -1;
	tab = malloc(ft_strlen(env)  * sizeof(char));
	while (env[++i])
		tab[i] = env[i];
	return (tab);
}

char	**changeenv(t_data *data, char **env)
{
	int	i;

	i = 0;
	data->newenv = malloc(10000 * sizeof(char *));
	while (env[i])
	{
		data->newenv[i] = ft_copystring(env[i]);
		i++;
	}
	return (data->newenv);
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
