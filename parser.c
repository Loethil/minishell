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

int	checkoption(char *splitl)
{
	int	i = 0;

	while (splitl[i])
	{
		if (splitl[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	cmd_set(t_data *data, t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	cmd->cmd = malloc (100 * sizeof(char *));
	cmd->otn = malloc (100 * sizeof(char *));
	cmd->arg = malloc (100 * sizeof(char *));
	cmd->cmd[j++] = data->splitl[i];
	while (data->splitl[++i])
	{
		if (ft_strcmp(data->splitl[i], "|") == 0)
		{
			cmd->cmd[j++] = data->splitl[i + 1];
			i++;
		}
		else if (checkoption(data->splitl[i]) == 1)
			cmd->otn[k++] = data->splitl[i];
		else if (data->splitl[i])
			cmd->arg[l++] = data->splitl[i];
	}
	i = 0;
	while (cmd->cmd[i])
		printf("cmd = %s\n", cmd->cmd[i++]);
	i = 0;
	while (cmd->otn[i])
		printf("otn = %s\n", cmd->otn[i++]);
	i = 0;
	while (cmd->arg[i])
		printf("arg = %s\n", cmd->arg[i++]);
	return (0);
}

char	*quotes(char *line, char *tab, int *i)
{
	int	j = 0;

	if (line[*i] == '"')
		while (line[++(*i)] != '"' && line[*i])
				tab[j++] = line[*i];
	else if (line[*i] == 39)
		while (line[++(*i)] != 39 && line[*i])
			tab[j++] = line[*i];
	else if (line[*i] == '|')
			tab[j++] = line[*i];
	else
		while (line[*i] != ' ' && line[*i] != '|' && line[*i])
			tab[j++] = line[(*i)++];
	tab[j] = '\0';
	return (tab);
}

char	**parser(t_data *data, t_cmd *cmd, char *line)
{
	int		i = -1;
	int		k = 0;
	char 	*tab;

	data->splitl = malloc (1000 * sizeof(char *));
	data->cnbr = 1;
	while (line[++i])
	{
		tab = malloc (1000 * sizeof(char));
		if (line[i] == ' ')
			continue ;
		tab = quotes(line, tab, &i);
		data->splitl[k++] = tab;
		tab = NULL;
		free (tab);
	}
	data->splitl[k] = NULL;
	cmd_set(data, cmd);
	return(data->splitl);
}