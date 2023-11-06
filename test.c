/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:45:59 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/06 13:46:01 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	data->all_path = ft_split(env[i] + 5, ':');
	i = 0;
	while (data->all_path[i])
	{
		data->all_path[i] = ft_strjoin(data->all_path[i], "/");
		i++;
	}
}

char	*get_access(t_data *data, char *tab)
{
	int	i;

	i = 0;
	if (access(tab, X_OK) == 0)
		return (tab);
	while (data->all_path[i])
	{
		data->true_path = ft_strjoin(data->all_path[i], tab);
		if (access(data->true_path, X_OK) == 0)
			return (data->true_path);
		i++;
	}
	write (1, "command not found\n", 18);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	if (s2[i])
		return (-1);
	return (0);
}

int	echo(t_data *data, char **tabsplit, char **env)
{
	if (execve(data->true_path, tabsplit, env) == -1)
	{
		printf("error execve\n");
		exit (0);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char *tab;
	char	**tabsplit;
	t_data	*data;
	int	 i = 0;

	find_path(data, env);
	while (1)
	{
		tab = readline("minishell:");
		add_history(tab);
		tabsplit = ft_split(tab, ' ');
		// printf("-%s\n", tab);
		// while (tabsplit[i])
		// 	printf("--%s\n", tabsplit[i++]);
		data->true_path = get_access(data, tabsplit[1]);
		if (ft_strcmp(tabsplit[1], "echo"))
			echo(data, tabsplit, env);
	}
}