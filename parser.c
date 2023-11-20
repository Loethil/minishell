/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:29:36 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/20 09:29:38 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_set(t_cmd *cmd)
{
	cmd->cmd = malloc (1000 * sizeof(char));
	cmd->otn = malloc (1000 * sizeof(char));
	cmd->arg = malloc (1000 * sizeof(char));
	if (!cmd->cmd || !cmd->otn || !cmd->arg)
		return (-1);
	return (0);
}

char	*test(t_data *data, char *line)
{
	int		i = 0;
	int		j = 0;
	char 	*tab;

	tab = malloc (1000 * sizeof(char));
	data->cnbr = 1;
	if (line[i] == '"')
		while (line[++i] != '"' && line[i])
			tab[j++] = line[i];
	else if (line[i] == 39)
		while (line[++i] != 39 && line[i])
			tab[j++] = line[i];
	else if (line[i] == '|')
		data->cnbr++;
	else
		while (line[i] != ' ' && line[i])
			tab[j++] = line[i++];
	tab[j] = '\0';
	return(tab);
}