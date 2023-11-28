/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:38:23 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/27 13:38:28 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct s_cmd
{
	char	**tab;
	char	*str;
	int		max;
	int		nbr;
}				t_cmd;

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_copystring(char *str)
{
	int		i;
	char	*tab;

	i = -1;
	tab = malloc(ft_strlen(str) * sizeof(char));
	while (str[++i])
		tab[i] = str[i];
	return (tab);
}

int	quotes(char *str, int *i, int j, int max)
{
	if (str[(*i)] == '\'')
	{
		while (str[++(*i)] != '\'' && (*i) < max)
			;
		if (str[*i] != '\'' && (*i) == max)
			return (-1);
		j++;
	}
	else if (str[(*i)] == '"')
	{
		while (str[++(*i)] != '"' && (*i) < max)
			;
		if (str[*i] != '"' && (*i) == max)
			return (-1);
		j++;
	}
	return (j);
}

void	ft_quotes(t_cmd *cmd, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[(*i)] == '\'')
	{
		while (line[++(*i)] != '\'' && (*i) < cmd->max)
			cmd->str[j++] = line[(*i)];
	}
	else if (line[(*i)] == '"')
	{
		while (line[++(*i)] != '"' && (*i) < cmd->max)
			cmd->str[j++] = line[(*i)];
	}
	cmd->str[j] = '\0';
	(*i)++;
}

int	countword(char *str)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = ft_strlen(str);
	while (i < max)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			j = quotes(str, &i, j, max);
			if (j == -1)
				return (-1);
		}
		else if (str[i] == '|')
			j++;
		else if (str[i] != ' ')
		{
			while (str[i] != ' ' && i < max)
			{
				if (str[i] == '|')
					j += 2;
				i++;
			}
			j++;
		}
		i++;
	}
	return (j);
}

void	ft_word(t_cmd *cmd, char *line, int *i, int *j)
{
	while (cmd->str[(*i)] != ' ' && (*i) < cmd->max)
	{
		if (cmd->str[(*i)] == '|')
		{
			cmd->str[(*j)] = '\0';
			return ;
		}
		cmd->str[(*j)++] = line[(*i)++];
	}
	cmd->str[(*j)] = '\0';
	(*i)++;
}

void	ft_pipes(t_cmd *cmd, int *i)
{
	if (cmd->str[(*i) + 1] == '|')
		return ;
	if (cmd->str[(*i)] == '|' && (*i) == cmd->max)
		return ;
	cmd->str = "|";
	(*i)++;
}

void	ft_chevron(t_cmd *cmd, int *i)
{
	if (cmd->str[(*i)] == '<')
		cmd->str = "<";
	else
		cmd->str = ">";
	(*i)++;
}

char	*ft_getline(t_cmd *cmd, char *line, int *i)
{
	int	j;

	j = 0;
	cmd->str = ft_copystring(line);
	cmd->max = ft_strlen(line);
	if ((*i) >= cmd->max)
		return (NULL);
	while (cmd->str[(*i)] == ' ')
		(*i)++;
	if (cmd->str[(*i)] == '"' || cmd->str[(*i)] == '\'')
		ft_quotes(cmd, line, i);
	else if (cmd->str[(*i)] == '|')
		ft_pipes(cmd, i);
	else if (cmd->str[(*i)] == '<' || cmd->str[(*i)] == '>')
		ft_chevron(cmd, i);
	else if (cmd->str[(*i)] != ' ')
		ft_word(cmd, line, i, &j);
	return (cmd->str);
}

void	get_tab(t_cmd *cmd, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd->tab = malloc (cmd->nbr * sizeof(char *));
	while (j < cmd->nbr)
	{
		cmd->tab[j] = ft_getline(cmd, line, &i);
		printf("%s\n", cmd->tab[j]);
		j++;
	}
	cmd->tab[j] = NULL;
}

int	main(int argc, char **argv)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	cmd = malloc (2 * sizeof(t_cmd));
	while (1)
	{
		line = readline("minishell:");
		if (line[0] == '\0')
			continue ;
		add_history(line);
		if (countword(line) == -1)
		{
			printf("error quotes\n");
			return (-1);
		}
		cmd->nbr = countword(line);
		get_tab(cmd, line);
		free(line);
	}
}
