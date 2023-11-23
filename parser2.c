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

char **splitcmd(t_data *data, char *line)
{
	int		i;
	int		j;
	int		k;
	char 	**splitl;

	i = -1;
	j = -1;
	splitl = malloc (data->nbr * sizeof(char *));
	while (line[++i])
	{
		k = 0;
		j++;
		splitl[j] = malloc (ft_strlen(line) * sizeof(char));
		if (!splitl[j])
			return (NULL);
		while (line[i] != '|' && line[i])
		{
			if (line[i] == '"')
				while (line[++i] != '"' && line[i])
					splitl[j][k++] = line[i];
			else if (line[i] == '\'')
				while (line[++i] != '\'' && line[i])
					splitl[j][k++] = line[i];
			else if (line[i])
					splitl[j][k++] = line[i];
			i++;
		}
		splitl[j][k] = '\0';
		splitl[j] = ft_strtrim(splitl[j], " ");
	}
	splitl[data->nbr] = NULL;
	i = 0;
	while (splitl[i])
		printf("%s\n", splitl[i++]);
	return (splitl);
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
		printf("error\n");
		return ;
	}
	cmd = malloc (data->nbr * sizeof(t_cmd));
	ft_cmd_set(cmd, data, line);
	data->splitl = splitcmd(data, line);
}

// int	main(int argc, char **argv)
// {
// 	if (argc < 1)
// 		return (-1);
// 	printf("%d\n", countcmd(argv[1]));
// 	return (0);
// }