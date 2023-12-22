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

char	**ft_copy_env(char **dst_env, char **src_env)
{
	int	i;

	i = 0;
	while (src_env[i])
	{
		dst_env[i] = src_env[i];
		i++;
	}
	dst_env[i] = NULL;
	return (dst_env);
}

int	ft_export_no_args(t_dta *dta)
{
	int		i;
	int		j;
	char	**env;

	i = -1;
	env = ft_calloc(ft_tablen(dta->newenv) + 1, sizeof(char *));
	env = ft_copy_env(env, dta->newenv);
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
	free(env);
	return (dta->res);
}
