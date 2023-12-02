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
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i])
		return (-1);
	return (0);
}

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(src);
	j = -1;
	while (++j < i + 1)
		dst[j] = src[j];
	dst[j] = '\0';
	return (dst);
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
	if (access(cmd, X_OK) == 0)
			return (cmd);
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

// gerer les cas ou nbr est plus grands qu'un long long
long long	ft_atoll(const char *str)
{
	long long	res;
	int	o;
	int	s;

	o = 0;
	res = 0;
	s = 0;
	if (str[o++] == '-' )
		s++;
	while (str[o] && (ft_isdigit(str[o]) == 1))
		res = res * 10 + str[o++] - '0';
	if (s == 1)
		return (-res);
	return (res);
}
