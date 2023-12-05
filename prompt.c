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
	while (line[i] && line[i] == ' ')
		i++;
	if (i != ft_strlen(line))
		return (0);
	return (1);
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
			continue ;
		if (g_sig.sigint == 1)
		{
			g_sig.sigint = 0;
			free(dta->line);
			dta->line = NULL;
			continue ;
		}
		add_history(dta->line);
		ft_set_up(dta, dta->line);
		// ft_whoitis(dta, cmd);
	}
}
