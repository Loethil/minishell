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

void	ft_print_echo(char **arg, t_dta *dta, int i)
{
	(void)dta;
	while (arg[i])
	{
		if (ft_tablen(arg) < 2 || i == ft_tablen(arg) - 1)
			printf("%s", arg[i]);
		else
			printf("%s ", arg[i]);
		i++;
	}
	dta->res = 0;
}

int	ft_sub_echo(char *arg, int j)
{
	while (arg[j] && arg[j] == 'n')
		j++;
	return (j);
}

void	ft_echo(t_dta *dta, t_cmd *cmd, int i)
{
	int	j;

	if (cmd->arg[0] == NULL)
		printf("\n");
	else if (ft_strncmp(cmd->arg[0], "-n", 2) == 0)
	{
		while (ft_strncmp(cmd->arg[i], "-n", 2) == 0)
		{
			j = ft_sub_echo(cmd->arg[i], 1);
			if (cmd->arg[i][j])
			{
				ft_print_echo(cmd->arg, dta, i);
				return ;
			}
			i++;
		}
		ft_print_echo(cmd->arg, dta, i);
	}
	else
	{
		ft_print_echo(cmd->arg, dta, i);
		printf("\n");
	}
	dta->ext_val = 0;
}
