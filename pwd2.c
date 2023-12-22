/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:36:46 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/19 11:36:47 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sub_dot_cd(t_dta *dta, int i)
{
	int	j;

	j = ft_strlen(dta->newenv[i]) - 1;
	while (dta->newenv[i][j - 1] != '/')
		j--;
	dta->newenv[i][j] = '\0';
}

void	ft_dot_cd(t_dta *dta, char *path, int i)
{
	int	j;
	int	k;

	k = -1;
	path = ft_check_slash(path);
	if (ft_chdir_err(path))
		return ;
	while (path[++k])
	{
		if (path[k] == '.' && path[k + 1] == '.')
		{
			ft_sub_dot_cd(dta, i);
			k += 2;
		}
		else if (path[k])
		{
			dta->newenv[i] = ft_check_slash(dta->newenv[i]);
			j = ft_strlen(dta->newenv[i]);
			while (path[k] != '/')
				dta->newenv[i][j++] = path[k++];
			dta->newenv[i][j] = '\0';
		}
	}
}

int	ft_chdir_err(char *path)
{
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

void	ft_sub_cd(t_dta *dta, char *path, int i)
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
		dta->newenv[i] = ft_strjoin("PWD=", new_path);
		ft_chdir_err(new_path);
		return ;
	}
	l = 2;
	while (path[l])
		new_path[k++] = path[l++];
	new_path[k] = '\0';
	dta->newenv[i] = ft_strjoin("PWD=", new_path);
	ft_chdir_err(new_path);
}
