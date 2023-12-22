/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:11:11 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/19 14:11:12 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (i < ft_tablen(tab))
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_builtin(t_dta *dta, t_cmd *cmd)
{
	(void)dta;
	if (cmd->cmd != NULL)
		ft_free_tab(cmd->cmd);
	if (cmd->arg != NULL)
		ft_free_tab(cmd->arg);
	if (cmd->rdr != NULL)
		ft_free_tab(cmd->rdr);
	free(cmd->lne);
	free(cmd);
	free(dta->tab);
}

void	ft_free_cmd(t_dta *dta, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < dta->pnbr)
	{
		if (cmd[i].cmd != NULL)
			ft_free_tab(cmd[i].cmd);
		if (cmd[i].arg != NULL)
			ft_free_tab(cmd[i].arg);
		if (cmd[i].rdr != NULL)
			ft_free_tab(cmd[i].rdr);
		if (cmd[i].tpath != NULL)
			free(cmd[i].tpath);
		free(cmd[i].lne);
		i++;
	}
	free(cmd);
	free(dta->tab);
	ft_free_tab(dta->all_path);
}
