/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:38:23 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/27 13:38:28 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_check_chevron(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (0);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (0);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (0);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (0);
	return(1);
}

void	ft_pars(t_cmd *cmd, char **tab)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	cmd[j].lne[0] = tab[i];
	cmd[j].cmd[0] = tab[i++];
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|") == 0)
		{
			j++;
			cmd[j].cmd[ft_tablen(cmd[j].cmd)] = tab[++i];
			cmd[j].lne[ft_tablen(cmd[j].lne)] = tab[i];
		}
		else if (ft_check_chevron(tab[i]) == 0)
		{
			cmd[j].rdr[ft_tablen(cmd[j].rdr)] = tab[i++];
			cmd[j].rdr[ft_tablen(cmd[j].rdr)] = tab[i];
		}
		else
		{
			cmd[j].arg[ft_tablen(cmd[j].arg)] = tab[i];
			cmd[j].lne[ft_tablen(cmd[j].lne)] = tab[i];
		}
		i++;
	}
}


void	ft_cmd_init(t_dta *dta, t_cmd *cmd, char **tab)
{
	int	j;

	j = 0;
	while (j < dta->pnbr)
	{
		cmd[j].lne = ft_calloc (ft_tablen(tab) + 1, sizeof(char *));
		cmd[j].cmd = ft_calloc (ft_tablen(tab) + 1, sizeof(char *));
		cmd[j].arg = ft_calloc (ft_tablen(tab) + 1, sizeof(char *));
		cmd[j].rdr = ft_calloc (ft_tablen(tab) + 1, sizeof(char *));
		j++;
	}
}

int	check_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", len) == 0)
		return (1);
	return (0);
}

int	cmd_simple(t_dta *dta, t_cmd *cmd)
{
	int	svg_out;

	svg_out = dup(STDOUT_FILENO);
	ft_redirect(dta, cmd);
	ft_whoitis(dta, cmd);
	if (dup2(svg_out, STDOUT_FILENO) == -1)
			error(cmd, dta, "error");
	return (0);
}

void	ft_set_up(t_dta *dta, char *line)
{
	t_cmd	*cmd;

	if (ft_countword(dta, line) == -1)
	{
		printf("error quotes\n");
		return ;
	}
	dta->nbr = ft_countword(dta, line);
	dta->var = NULL;
	cmd = ft_calloc(dta->pnbr + 1, sizeof(t_cmd));
	ft_create_tab(dta, line);
	ft_cmd_init(dta, cmd, dta->tab);
	ft_pars(cmd, dta->tab);
	if (dta->pnbr == 1 && check_builtin(cmd->cmd[0]) == 1)
		if (cmd_simple(dta, cmd) == 0)
			return ;
	pipex(dta, cmd);
}
