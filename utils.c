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
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	if (s2[i])
		return (-1);
	return (0);
}

char	**find_path(t_data *data, char **env)
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
	return(data->all_path);
} //obselete a changer par getenv(path)

char	*get_access(t_data *data, char *argv)
{
	int	i;

	i = 0;
	if (access(argv, X_OK) == 0)
		return (argv);
	while (data->all_path[i])
	{
		data->true_path = ft_strjoin(data->all_path[i], argv);
		if (access(data->true_path, X_OK) == 0)
			return (data->true_path);
		free(data->true_path);
		i++;
	}
	write (1, "command not found\n", 18);
	exit(1);
}

