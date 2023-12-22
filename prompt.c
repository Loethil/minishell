/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:07:17 by scarpent          #+#    #+#             */
/*   Updated: 2023/11/23 15:07:18 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_whitespace(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (i != ft_strlen(line))
		return (0);
	return (1);
}

int	ft_set_cmd(t_dta *dta, t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_find_path(dta);
	while (i < dta->pnbr)
	{
		cmd[i].tpath = ft_get_access(dta, cmd[i].cmd[0]);
		i++;
	}
	return (0);
}

void	ft_prompt(t_dta *dta)
{
	while (1)
	{
		dta->line = readline("minishell: ");
		if (dta->line == NULL)
		{
			printf("exit\n");
			return ;
		}
		if (dta->line[0] == '\0' || ft_whitespace(dta->line))
		{
			free(dta->line);
			continue ;
		}
		add_history(dta->line);
		if (g_sigint)
		{
			g_sigint = 0;
			dta->ext_val = 130;
		}
		ft_set_up(dta, dta->line);
		free(dta->line);
	}
}
