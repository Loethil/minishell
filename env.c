/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:21:29 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/14 15:21:31 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_find_path(t_data *data)
{
	int	i;

	i = 0;
	data->all_path = ft_split(getenv("PATH"), ':');
	while (data->all_path[i])
	{
		data->all_path[i] = ft_strjoin(data->all_path[i], "/");
		i++;
	}
	return(data->all_path);
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

void	ft_pwdorenv(char **newenv, char *tab)
{
	int	i;

	if ( strcmp(tab, "PWD") == 0)
	{
		i = ft_findpwd(newenv);
		printf("%s\n", newenv[i] + 4);
	}
	if (strcmp(tab, "ENV") == 0)
	{
		i = 0;
		while(newenv[i])
			printf("%s\n", newenv[i++]);
	}
}

char	*ft_get_access(t_data *data, char *cmd)
{
	int	i;

	i = 0;
	while (data->all_path[i])
	{
		data->true_path = ft_strjoin(data->all_path[i], cmd);
		if (access(data->true_path, X_OK) == 0)
			return (data->true_path);
		free(data->true_path);
		i++;
	}
	printf("%s command not found\n", cmd);
	exit(1);
}