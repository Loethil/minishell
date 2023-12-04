/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:00:54 by scarpent          #+#    #+#             */
/*   Updated: 2023/11/14 12:00:55 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_print_echo(char **arg, int i)
{
	while (arg[i])
	{
		if (ft_tablen(arg) <= 2 || i == ft_tablen(arg) - 1)
			printf("%s", arg[i]);
		else
			printf("%s ", arg[i]);
		i++;
	}
}

int	ft_echo(t_dta *dta, t_cmd *cmd, int i)
{
	int	j;

	(void)dta;
	if (strncmp(cmd->arg[0], "-n", 2) == 0)
	{
		while (strncmp(cmd->arg[i], "-n", 2) == 0)
		{
			j = 1;
			while (cmd->arg[i][j] == 'n')
				j++;
			if (cmd->arg[i][j])
			{
				ft_print_echo(cmd->arg, i);
				return (0);
			}
			i++;
		}
		ft_print_echo(cmd->arg, i);
	}
	else
	{
		ft_print_echo(cmd->arg, i);
		printf("\n");
	}
	return (0);
}
