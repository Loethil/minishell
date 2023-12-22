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

int	ft_check_dot(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_check_slash(char *path)
{
	int	i;

	i = ft_strlen(path);
	if (path[i - 1] != '/')
	{
		path[i++] = '/';
		path[i] = '\0';
		return (path);
	}
	return (path);
}

char	*ft_chdir(t_dta *dta, char *true_path, char *path, int i)
{
	true_path = ft_strjoin("", dta->newenv[i] + 4);
	if (ft_strncmp("/home", path, 5) == 0)
		true_path = ft_strjoin("", path);
	else
		true_path = ft_strjoin(true_path, path);
	dta->newenv[i] = ft_strjoin("PWD=", true_path);
	return (true_path);
}

void	ft_changedir(t_dta *dta, t_cmd *cmd, char *path)
{
	int	i;

	i = ft_findpwd(dta->newenv);
	if (cmd->arg[1])
	{
		dta->ext_val = 1;
		printf("minishell: cd: too many args\n");
		return ;
	}
	if (!path)
		path = "~";
	if (!path[0])
		return ;
	if (path[0] == '~')
		ft_sub_cd(dta, path, i);
	else if (ft_check_dot(path))
		ft_dot_cd(dta, path, i);
	else
	{
		if (ft_chdir_err(path))
			return ;
		path = ft_check_slash(path);
		dta->true_path = ft_chdir(dta, dta->true_path, path, i);
	}
}
