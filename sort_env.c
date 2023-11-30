/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:23:49 by scarpent          #+#    #+#             */
/*   Updated: 2023/11/28 14:23:51 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_swap(char **env, int i)
{
	char	*temp;

	temp = env[i];
	env[i] = env[i + 1];
	env[i + 1] = temp;
	return (env);
}

char	**ft_sort_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i + 1])
	{
		if (ft_strcmp(env[i], env[i + 1]) > 0)
		{
			env = ft_swap(env, i);
			i = 0;
		}
	}
	if (ft_strcmp(env[0], env[1]) > 0)
	{
		i = 0;
		while (env[i + 1])
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				env = ft_swap(env, i);
				i = 0;
			}
			i++;
		}
	}
	return (env);
}

void	ft_export_no_args(t_data *data)
{
	int		i;
	int		j;
	char	**env;

	i = -1;
	env = malloc(sizeof(char *) * (ft_tablen(data->newenv) + 1));
	env = data->newenv;
	env = ft_sort_env(env);
	while (env[++i])
	{
		if (env[i][0] == '_')
			continue ;
		j = 0;
		printf("declare -x ");
		while (env[i][j] && env[i][j - 1] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		printf("\"");
		while (env[i][j])
			printf("%c", env[i][j++]);
		printf("\"\n");
	}
}
