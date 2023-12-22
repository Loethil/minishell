/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:48:21 by mbatteux          #+#    #+#             */
/*   Updated: 2023/12/19 17:48:23 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tabs(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_error(t_cmd *cmd, t_dta *dta, char *err)
{
	perror (err);
	ft_free_cmd(dta, cmd);
	exit (-1);
}

void	ft_exit(t_dta *dta, t_cmd *cmd)
{
	char	*chk;

	printf ("exit\n");
	if (cmd->arg[0] == NULL)
		exit (0);
	dta->ext = ft_atoll(cmd->arg[0]);
	chk = ft_itoa(dta->ext);
	if (ft_strcmp(cmd->arg[0], chk) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->arg[0]);
		exit (2);
	}
	dta->ext %= 256;
	if (cmd->arg[1])
	{
		printf("minishell: exit: too many arguments\n");
		dta->ext_val = 1;
		return ;
	}
	exit(dta->ext);
}
