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

void	ft_var_alloc(t_dta *dta, char *cmd, int i)
{
	int	j;

	j = 0;
	dta->var = ft_calloc(ft_strlen(cmd), sizeof(char));
	while (cmd[i])
		dta->var[j++] = cmd[i++];
}

void	ft_print_var(t_dta *dta)
{
	int	i;
	int	j;

	i = -1;
	while (dta->newenv[++i])
	{
		if (ft_strncmp(dta->newenv[i], dta->var, ft_strlen(dta->var)) == 0)
		{
			j = 0;
			while (dta->newenv[i][j] != '=')
				j++;
			if (dta->newenv[i][j] == '=' && dta->newenv[i][j])
				j++;
			else
			{
				printf("\n");
				return ;
			}
			while (dta->newenv[i][j] && dta->newenv[i][j] != '\n')
				printf("%c", dta->newenv[i][j++]);
		}
	}
}

int	ft_var_hdl(t_dta *dta, char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '$' && i == 0)
		{
			i++;
			ft_var_alloc(dta, cmd, i);
			return (1);
		}
		else if (cmd[i] == '$' && i)
		{
			i = 0;
			while (cmd[i] != '$')
				printf("%c", cmd[i++]);
			i++;
			ft_var_alloc(dta, cmd, i);
			return (1);
		}
	}
	return (0);
}

void	ft_print_echo(char **arg, t_dta *dta, int i)
{
	while (arg[i])
	{
		if (ft_var_hdl(dta, arg[i]))
		{
			if (i == ft_tablen(arg) - 1)
				ft_print_var(dta);
			else
			{
				ft_print_var(dta);
				printf(" ");
			}
		}
		else if (ft_tablen(arg) < 2 || i == ft_tablen(arg) - 1)
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
	if (ft_strncmp(cmd->arg[0], "-n", 2) == 0)
	{
		while (ft_strncmp(cmd->arg[i], "-n", 2) == 0)
		{
			j = 1;
			while (cmd->arg[i][j] == 'n')
				j++;
			if (cmd->arg[i][j])
			{
				ft_print_echo(cmd->arg, dta, i);
				return (0);
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
	return (0);
}
