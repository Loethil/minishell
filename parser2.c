/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:37:15 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/22 15:37:17 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkoption(char *line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	countcmd(char *line)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			while (line[++i] != '"')
				if (!line[i])
					return (-1);
		}
		else if (line[i] == '\'')
		{
			while (line[++i] != '\'')
				if (!line[i])
					return (-1);
		}
		else if (line[i] == '|')
		{
			if (line[i + 1] == '|' || line[i + 1] =='\0')
				return (-1);
			j++;
		}
	}
	return (j + 1);
}

void	splitexe(t_cmd *cmd, t_data *data)
{
	int	i;
	int	j;
	char	**line;

	i = 0;
	j = 0;
	while (i < data->nbr)
	{
		line = ft_split(cmd[i].exe, ' ');
		cmd[i].cmd = line[j++];
		while (line[j] && ft_checkoption(line[j]) == 1)
		{
			cmd[i].otn = ft_strjoin(cmd[i].otn, line[j++]);
		}
		while (line[j])
		{
			printf("line ===%s\n", line[j]);
			cmd[i].arg = ft_strjoin(cmd[i].arg, line[j++]);
		}
		j = 0;
		i++;
	}
	i = 0;
	while (i < data->nbr)
	{
		printf("exe = %s\n", cmd[i].exe);
		printf("cmd = %s\n", cmd[i].cmd);
		printf("otn = %s\n", cmd[i].otn);
		printf("arg = %s\n", cmd[i].arg);
		i++;
	}
}

// char **splitcmd(t_data *data, t_cmd *cmd, char *line)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char 	**splitl;

// 	i = -1;
// 	j = -1;
// 	splitl = malloc (data->nbr * sizeof(char *));
// 	while (line[++i])
// 	{
// 		k = 0;
// 		j++;
// 		splitl[j] = malloc (ft_strlen(line) * sizeof(char));
// 		if (!splitl[j])
// 			return (NULL);
// 		while (line[i] != '|' && line[i])
// 		{
// 			if (line[i] == '"')
// 			{
// 				splitl[j][k++] = line[i];
// 				while (line[++i] != '"' && line[i])
// 					splitl[j][k++] = line[i];
// 				splitl[j][k++] = line[i];
// 			}
// 			else if (line[i] == '\'')
// 			{
// 				splitl[j][k++] = line[i];
// 				while (line[++i] != '\'' && line[i])
// 					splitl[j][k++] = line[i];
// 				splitl[j][k++] = line[i];
// 			}
// 			else if (line[i])
// 					splitl[j][k++] = line[i];
// 			i++;
// 		}
// 		splitl[j][k] = '\0';
// 		splitl[j] = ft_strtrim(splitl[j], " ");
// 		cmd[j].exe = splitl[j];
// 	}
// 	splitl[data->nbr] = NULL;
// 	return (splitl);
// }

void	splitcmd(t_cmd *cmd, char *line)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	while (i < countcmd(line))
	{
		k = 0;
		j++;
		while (line[i] != '|' && line[i])
		{
			if (line[i] == '"')
			{
				cmd[i].exe[k++] = line[i];
				while (line[++i] != '"' && line[i])
					cmd[i].exe[k++] = line[i];
				cmd[i].exe[k++] = line[i];
			}
			else if (line[i] == '\'')
			{
				cmd[i].exe[k++] = line[i];
				while (line[++i] != '\'' && line[i])
					cmd[i].exe[k++] = line[i];
				cmd[i].exe[k++] = line[i];
			}
			else if (line[i])
					cmd[i].exe[k++] = line[i];
			i++;
		}
		cmd[i].exe[k] = '\0';
		cmd[i].exe = ft_strtrim(cmd[i].exe, " ");
	}
}

int	ft_cmd_set(t_cmd *cmd, t_data *data, char *line)
{
	int	i;

	i = 0;
	while (i < data->nbr)
	{
		cmd[i].exe = malloc (ft_strlen(line) * sizeof (char));
		cmd[i].cmd = malloc (ft_strlen(line) * sizeof (char));
		cmd[i].otn = malloc (ft_strlen(line) * sizeof (char));
		cmd[i].arg = malloc (ft_strlen(line) * sizeof (char));
		if (!cmd[i].exe || !cmd[i].cmd || !cmd[i].otn || !cmd[i].arg)
			return (-1);
		i++;
	}
	return (0);
}

void	parser(t_data *data, char *line)
{
	t_cmd	*cmd;

	data->nbr = countcmd(line);
	if (data->nbr == -1)
	{
		printf("error pipe ou quotes\n");
		return ;
	}
	cmd = malloc (data->nbr * sizeof(t_cmd));
	ft_cmd_set(cmd, data, line);
	splitcmd(cmd, line);
	// splitexe(cmd, data);
}