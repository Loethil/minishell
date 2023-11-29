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
	char	**tab;  //stock la ligne entiere dans un char **
	char	*str;	//stock la string de readline
	int		nbr;    //nombre de mot
	int		max;    //taille de line
	int		pnbr;   //pipe nbr
}				t_cmd;

typedef	struct s_exe
{
	char	**exe; //stock la cmd jusqu'a un pipe ou fin si une seul commande
	char	**cmd; //stock la cmd et ses options
	char	**arg; //stock les arguments de la commande
	char	*rdr;  //stock les arg de la redirection
	int		dlr;   // dollar macro
}				t_exe;

int	ft_checkoption(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (str[i] == '-')
			return (1);
		else if (str[(i)] == '\'')
		{
			while (str[++(i)] != '\'' && str[i])
				;
		}
		else if (str[(i)] == '"')
		{
			while (str[++(i)] != '"' && str[i])
				;
		}
		i++;
	}
	return (0);
}

int	ft_lentab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i])
		return (-1);
	return (0);
}

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

int	countword(t_cmd *cmd, char *str)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	cmd->pnbr = 1;
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
		{
			cmd->pnbr++;
			j++;
		}
		else if (str[i] != ' ')
		{
			while (str[i] != ' ' && i < max)
			{
				if (str[i] == '|')
				{
					cmd->pnbr++;
					j += 2;
				}
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
		return ; //bug avec trop de pipes a regler
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

void	stock_cmd(t_cmd *cmd, t_exe *exe)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (j < cmd->pnbr)
	{
		if (!cmd->tab[i])
			return ;
		if (ft_strcmp(cmd->tab[i], "|") == 0)
		{
			k = 0;
			i++;
			j++;
		}
		exe[j].exe[k] = cmd->tab[i];
		printf("exe %d = %s\n", j, exe[j].exe[k]);
		k++;
		i++;
	}
}

void	set_data(t_cmd *cmd, t_exe *exe)
{
	int	i;

	i = 0;
	while (i < cmd->pnbr)
	{
		exe[i].exe = malloc (1000 * sizeof(char *));
		i++;
	}
}

void	range(t_cmd *cmd, t_exe exe)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	j = 0;
	exe.cmd[j++] = exe.exe[i++];  
	while (i < ft_tablen(exe.exe))
	{
		if (ft_checkoption(exe.exe[i]) == 1)
			exe.cmd[j++] = exe.exe[i];
		else if (ft_checkoption(exe.exe[i] == 0))
			exe.arg[k++] = exe.exe[i];
		else if (ft_checkredir(exe.exe[i] == 1))
			exe.rdr = exe.exe[i + 1]; // pas sure de sa
		i++;
	}
	// possible fonctionnement mais a revoir demain
	// prototype d'un'rangeur'
}

int	main(int argc, char **argv)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	cmd = malloc (sizeof(t_cmd));
	while (1)
	{
		line = readline("minishell:");
		if (line[0] == '\0')
			continue ;
		add_history(line);
		if (countword(cmd, line) == -1)
		{
			printf("error quotes\n");
			return (-1);
		}
		t_exe	*exe;

		exe = malloc (100 * sizeof(t_exe));
		cmd->nbr = countword(cmd, line);
		get_tab(cmd, line);
		set_data(cmd, exe);
		stock_cmd(cmd, exe);
	}
}
