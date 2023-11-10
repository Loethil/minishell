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
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i])
		return (-1);
	return (0);
}

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
