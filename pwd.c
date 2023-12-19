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

char	*ft_new_path(t_dta *dta, int i)
{
	int		j;
	int		k;
	char	*new_path;

	j = 0;
	k = 0;
	new_path = ft_calloc(ft_strlen(dta->newenv[i]) + 1, sizeof(char));
	while (dta->newenv[i][j] && dta->newenv[i][j - 1] != '=')
		j++;
	while (dta->newenv[i][j] && dta->newenv[i][j] != 'D')
		new_path[k++] = dta->newenv[i][j++];
	new_path[k] = '\0';
	return (new_path);
}

char	*ft_check_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
	{
		path[ft_strlen(path)] = '/';
		path[ft_strlen(path) + 1] = '\0';
		return (path);
	}
	return (path);
}

void	ft_changedir(t_dta *dta, char *path)
{
	int	i;

	i = ft_findpwd(dta->newenv);
	if (!path)
		path = "~";
	if (!path[0])
		return ;
	if (path[0] == '~')
		ft_sub_cd(dta, path, i);
	else if (path[0] == '.')
	{
		ft_dot_cd(dta, path, i);
		ft_chdir_err(path);
	}
	else
	{
		path = ft_check_slash(path);
		dta->true_path = ft_strjoin("", dta->newenv[i] + 4);
		if (ft_strncmp("/home", path, 5) == 0)
			dta->true_path = ft_strjoin("", path);
		else
			dta->true_path = ft_strjoin(dta->true_path, path);
		dta->newenv[i] = ft_strjoin("PWD=", dta->true_path);
		ft_chdir_err(dta->true_path);
	}
}
