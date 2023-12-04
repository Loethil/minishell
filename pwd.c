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

void	ft_pwdorenv(char **newenv, char *tab)
{
	int	i;

	if (strcmp(tab, "PWD") == 0)
	{
		i = ft_findpwd(newenv);
		printf("%s\n", newenv[i] + 4);
	}
	if (strcmp(tab, "ENV") == 0)
	{
		i = 0;
		while(newenv[i])
			printf("%s\n", newenv[i++]);
	}
}

void	ft_changedir(t_dta *dta, char *path)
{
	int	i;

	i = ft_findpwd(dta->newenv);
	if (path[0] == '~')
	{
		dta->newenv[i] = ft_strjoin("PWD=/home/mbatteux", path + 1);
		path = ft_strjoin("/home/mbatteux/", path + 1);
		if (chdir(path) == -1)
			printf("ERROR CHDIR\n");
		return ;
	}
	dta->true_path = ft_strjoin(dta->newenv[i], "/");
	dta->true_path = ft_strjoin(dta->true_path, path);
	dta->newenv[i] = dta->true_path;
	if (chdir(path) == -1)
		printf("ERROR CHDIR\n");
}
