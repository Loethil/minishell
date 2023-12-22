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
	while (1)
	{
		if (tab[i] == NULL)
		{
			free(tab);
			return ;
		}
		free(tab[i]);
		i++;
	}
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
		free(&cmd[i]);
		i++;
	}
	ft_free_tab(dta->all_path);
}

void	ft_destroy(t_dta *dta)
{
	free(dta->var);
	free(dta->pwd);
	//free(dta->buf);
	free(dta->str);
}
