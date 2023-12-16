/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:09:08 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/02 15:09:09 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dot_cd(t_dta *dta, char *path, int i)
{
	int	j;
	int	k;

	k = 0;
	while (path[k])
	{
		if (path[k] == '.' && path[k + 1] == '.')
		{
			j = ft_strlen(dta->newenv[i]) - 1;
			while (dta->newenv[i][j] != '/')
				j--;
			dta->newenv[i][j] = '\0';
			if (chdir(path) == -1)
				printf("minishell: cd: %s: No such file or directory\n", path);
			k++;
		}
		k++;
	}
}

void	ft_chdir_err(char *path)
{
	if (chdir(path) == -1)
		printf("minishell: cd: %s: No such file or directory\n", path);
}

char	*ft_sub_cd(t_dta *dta, char *path, int i)
{
	int		j;
	int		k;
	int		l;
	char	*new_path;

	j = 0;
	k = 0;
	while (dta->newenv[i][j] && dta->newenv[i][j - 1] != '=')
		j++;
	new_path = ft_calloc(ft_strlen(dta->newenv[i]) + ft_strlen(path),
			sizeof(char));
	while (dta->newenv[i][j] && dta->newenv[i][j] != 'D')
		new_path[k++] = dta->newenv[i][j++];
	if (!path[1])
	{
		dta->newenv[i][j - 1] = '\0';
		return (new_path);
	}
	l = 2;
	while (path[l])
		new_path[k++] = path[l++];
	new_path[k] = '\0';
	dta->newenv[i] = new_path;
	path = dta->newenv[i];
	return (path);
}

void	ft_changedir(t_dta *dta, char *path)
{
	int	i;

	i = ft_findpwd(dta->newenv);
	if (!path)
		path = "~";
	if (path[0] == '~')
	{
		path = ft_sub_cd(dta, path, i);
		ft_chdir_err(path);
		exit (0);
	}
	if (path[0] == '.')
	{
		ft_dot_cd(dta, path, i);
		exit (0);
	}
	if (!path[0])
		exit (0);
	dta->true_path = ft_strjoin(dta->newenv[i], "/");
	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	dta->true_path = ft_strjoin(dta->true_path, path);
	dta->newenv[i] = dta->true_path;
	ft_chdir_err(path);
	exit (0);
}
