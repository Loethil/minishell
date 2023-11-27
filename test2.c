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

typedef	struct s_cmd
{
	char	**tab;
	char	*tmp;
	char	*stk;
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
	int	i;
	char	*tab;

	i = -1;
	tab = malloc(ft_strlen(str)  * sizeof(char));
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
		j++;	
	}
	else if (str[(*i)] == '"')
	{
		while (str[++(*i)] != '"' && (*i) < max)
			;
		j++;	
	}
	return (j);
}

int	countword(char *str)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = ft_strlen(str);
	// printf("%d\n", ft_strlen(str));
	// printf("%s\n", str);
	while (i < max)
	{
		if (str[i] == '"' || str[i] == '\'')
			j = quotes(str, &i, j, max);
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



char *ft_quotes(t_cmd *cmd, char *line, int *i)
{
	int j = 0;

	if (line[(*i)] == '\'')
	{
		while (line[++(*i)] != '\'' && (*i) < cmd->max)
			cmd->tmp[j++] = line[(*i)];
	}
	else if (line[(*i)] == '"')
	{
		while (line[++(*i)] != '"' && (*i) < cmd->max)
			cmd->tmp[j++] = line[(*i)];
	}
	cmd->tmp[j] = '\0';
	return (cmd->tmp);
}

char	*ft_getline(t_cmd *cmd, char *line, int *i)
{
	int	j = 0;

	cmd->tmp = ft_copystring(line);
	cmd->tmp[ft_strlen(line)] = '\0';
	cmd->max = ft_strlen(line);
	if ((*i) >= cmd->max)
		return (NULL);
	while (cmd->tmp[(*i)] == ' ')
			(*i)++;
	if (cmd->tmp[(*i)] == '"' || cmd->tmp[(*i)] == '\'')
	{
		ft_quotes(cmd, line, i);
		(*i)++;
	}
	else if (cmd->tmp[(*i)] == '|')
	{
		cmd->tmp = "|";
		(*i)++;
	}
	else if (cmd->tmp[(*i)] == '<' || cmd->tmp[(*i)] == '>')
	{
		if (cmd->tmp[(*i)] == '<')
			cmd->tmp = "<";
		else
			cmd->tmp = ">";
		(*i)++;
	}
	else if (cmd->tmp[(*i)] != ' ')
	{
		while ( cmd->tmp[(*i)] != ' ' && (*i) < ft_strlen(line))
		{
			if (cmd->tmp[(*i)] == '|')
			{
				cmd->tmp[j] = '\0';
				return (cmd->tmp);
			}
			cmd->tmp[j++] = line[(*i)++];
		}
		(*i)++;
		cmd->tmp[j] = '\0';
	}
	return (cmd->tmp);
}

void	get_tab(t_cmd *cmd, char *line)
{
	int	i = 0;
	int	j = 0;

	cmd->tab = malloc (cmd->nbr * sizeof(char *));
	while (j < cmd->nbr)
	{
		cmd->tab[j] = ft_getline(cmd, line, &i);
		printf("%s\n", cmd->tab[j]);
		// free(cmd->tmp);
		j++;
	}
	cmd->tab[j] = NULL;
}


int	main(int argc, char **argv)
{
	char *line;
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
		cmd->nbr = countword(line);
		get_tab(cmd, line);
		free(line);
	}
}
