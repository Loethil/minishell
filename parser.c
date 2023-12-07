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

void	ft_pars(t_cmd *cmd, char **tab)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	cmd[j].cmd[0] = tab[i++];
	cmd[j].cmd[1] = NULL; // uniquement pour printf bug resolu
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|") == 0)
		{
			j++;
			cmd[j].cmd[ft_tablen(cmd[j].cmd)] = tab[++i];
		}
		else if (ft_strncmp(tab[i], "-", 1) == 0) // faire en sorte que sa marche pour toutes les options
		{
			cmd[j].arg[ft_tablen(cmd[j].arg)] = tab[i];
			cmd[j].arg[ft_tablen(cmd[j].arg) + 1] = NULL; // uniquement pour printf bug resolu
		}
		else if (ft_strncmp(tab[i], "-", 1)) // modifie " > 0" pour le '$' ca marchait pas
			cmd[j].arg[ft_tablen(cmd[j].arg)] = tab[i];
		i++;
	} // marche du tonnerre juste a rajouter les redirs
}	//command apres le pipe non gerer, + redir + sa rendre sa plus beau
	// print le res
	// j = 0;
	// while (j < dta->pnbr)
	// {
	// 	i = 0;
	// 	while (i < ft_tablen(cmd[j].cmd))
	// 		printf("cmd [%d] = %s\n", j, cmd[j].cmd[i++]);
	// 	i = 0;
	// 	while (i < ft_tablen(cmd[j].arg))
	// 		printf("arg [%d] = %s\n", j, cmd[j].arg[i++]);
	// 	j++;
	// }

void	ft_cmd_init(t_dta *dta, t_cmd *cmd, char **tab)
{
	int	j;

	j = 0;
	while (j < dta->pnbr)
	{
		cmd[j].cmd = ft_calloc (ft_tablen(tab), sizeof(char *));
		cmd[j].arg = ft_calloc (ft_tablen(tab), sizeof(char *));
		j++;
	}
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
	cmd = ft_calloc(dta->pnbr, sizeof(t_cmd));
	ft_create_tab(dta, line);
	ft_cmd_init(dta, cmd, dta->tab);
	ft_pars(cmd, dta->tab);
	ft_whoitis(dta, cmd);
	//	dta->ext_val = 127;
}
