/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:41:33 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/06 13:41:36 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_sq_echo(char **arg, t_dta *dta, int i)
{
	int	j;

	(void)dta;
	while (arg[i])
	{
		j = 1;
		while (arg[i][j] && arg[i][j] != '\'')
			printf("%c", arg[i][j++]);
		i++;
	}
}

void	ft_sq_echo(t_dta *dta, t_cmd *cmd, int i)
{
	int	j;

	(void)dta;
	if (ft_strncmp(cmd->arg[0], "-n", 2) == 0)
	{
		while (ft_strncmp(cmd->arg[i], "-n", 2) == 0)
		{
			j = 1;
			while (cmd->arg[i][j] == 'n')
				j++;
			if (cmd->arg[i][j])
			{
				ft_print_sq_echo(cmd->arg, dta, i);
				return ;
			}
			i++;
		}
		ft_print_sq_echo(cmd->arg, dta, i);
	}
	else
	{
		ft_print_sq_echo(cmd->arg, dta, i);
		printf("\n");
	}
}

void ft_manage_echo(t_dta *dta, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[i])
	{
		if (cmd->arg[i][0] == '\'')
			ft_sq_echo(dta, cmd, 0);
		else
			ft_echo(dta, cmd, 0);
		i++;
	}
}
