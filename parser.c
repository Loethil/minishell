/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:38:23 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/27 13:38:28 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_set_cmd(t_dta *dta, t_cmd *cmd)
{
	int	i;

	i = 0;
	dta->all_path = ft_find_path(dta);
	while (i < dta->pnbr)
	{
		cmd[i].tpath = ft_get_access(dta, cmd[i].cmd[0]);
		i++;
	}
	return (0);
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
	// ft_free_tab(tab);
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

int	ft_cmd_simple(t_dta *dta, t_cmd *cmd)
{
	int	svg_out;

	svg_out = dup(STDOUT_FILENO);
	ft_redirect(dta, cmd);
	ft_whoitis(dta, cmd);
	if (dup2(svg_out, STDOUT_FILENO) == -1)
		ft_error(cmd, dta, "error");
	ft_free_cmd(dta, cmd);
	return (0);
}

int	ft_check_line(t_dta *dta, char *line)
{
	if (ft_countword(dta, line) == -1)
	{
		printf("error quotes\n");
		return (-1);
	}
	if (ft_countword(dta, line) == -2)
	{
		printf("error pipes\n");
		return (-1);
	}
	return (0);
}
