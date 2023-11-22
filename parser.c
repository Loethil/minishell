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

int	ft_checkoption(char *splitl)
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

int	ft_countword(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_cmd_set(t_data *data, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd->cmd = malloc (100 * sizeof(char *));
	cmd->otn = malloc (100 * sizeof(char *));
	cmd->arg = malloc (100 * sizeof(char *));
	cmd->cmd[0] = data->splitl[0];
	while (data->splitl[++i])
	{
		if (ft_strcmp(data->splitl[i], "|") == 0)
		{
			j = ft_countword(cmd->cmd);
			cmd->cmd[j] = data->splitl[i++ + 1];
		}
		else if (ft_checkoption(data->splitl[i]) == 1)
		{
			j = ft_countword(cmd->otn);
			cmd->otn[j] = data->splitl[i];
		}
		else if (data->splitl[i])
		{
			j = ft_countword(cmd->arg);
			cmd->arg[j] = data->splitl[i];
		}
	}
	// i = 0;
	// while (cmd->cmd[i])
	// 	printf("cmd = %s\n", cmd->cmd[i++]);
	// i = 0;
	// while (cmd->otn[i])
	// 	printf("otn = %s\n", cmd->otn[i++]);
	// i = 0;
	// while (cmd->arg[i])
	// 	printf("arg = %s\n", cmd->arg[i++]);
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

// void	parser(t_data *data, char *line)
// {
// 	int		i = -1;
// 	int		k = 0;
// 	char 	*tab;
// 	t_cmd	*cmd;

// 	data->splitl = malloc (1000 * sizeof(char *));
// 	cmd = malloc ((countcmd(line) + 1) * sizeof (t_cmd));
// 	while (line[++i])
// 	{
// 		tab = malloc (ft_strlen(line) * sizeof(char));
// 		if (line[i] == ' ')
// 			continue ;
// 		tab = quotes(line, tab, &i);
// 		data->splitl[k++] = tab;
// 		tab = NULL;
// 		free (tab);
// 	}
// 	data->splitl[k] = NULL;
// 	ft_cmd_set(data, cmd);
// 	return(data->splitl);
// }

// void	parser(t_data *data, char *line);
// {
// 	t_cmd	*cmd;
// 	int		i = -1;
// 	int		k = 0;

// 	cmd = malloc ((countcmd(line) + 1) * sizeof (t_cmd));
// 	data->splitl = malloc (1000 * sizeof(char *));
// 	while (line[++i])
// 	{
// 		tab = malloc (ft_strlen(line) * sizeof(char));
// 		if (line[i] == ' ')
// 			continue ;
// 		tab = quotes(line, tab, &i);
// 		cmd[k++]->exe = tab;
// 		tab = NULL;
// 		free (tab);
// 	}
// }