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

void	ft_print_sq_echo(char **arg, int i)
{
	int	j;

	j = 1;
	while (arg[i][j] && arg[i][j] != '\'')
		printf("%c", arg[i][j++]);
	if (ft_tablen(arg) < 2 || i == ft_tablen(arg) - 1)
		return ;
	else
		printf(" ");
}

void	ft_print_echo(char **arg, t_dta *dta, int i)
{
	while (arg[i])
	{
		if (arg[i][0] == '\'')
			ft_print_sq_echo(arg, i);
		else if (ft_var_hdl(arg[i]) == 1)
			ft_var_master(arg, dta, i);
		else if (ft_tablen(arg) < 2 || i == ft_tablen(arg) - 1)
			printf("%s", arg[i]);
		else
			printf("%s ", arg[i]);
		i++;
	}
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
				exit (0);
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
	exit (0);
}
