/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:31:30 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/27 10:31:34 by mbatteux         ###   ########.fr       */
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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
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

char	*returnword(char *line, int	*j)
{
	int	i = 0;
	int	j = 0;
	char	*tab;
	int	max = ft_strlen(line);

	tab = malloc (max * sizeof(char) + 1);
	while ((*j) < max)
	{
		if ()
		tab[i++] = line[(*j)++];
	}
	return (tab);
}


char	**cutline(char *line, int nbr)
{
	char **tab;
	int	i = 0;
	int	j = 0;

	tab = malloc (nbr * sizoef(char *) + 1);
	while (i < nbr)
	{
		tab[i] = returnword(line, &j);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	countnbr(char *str)
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

int	main(int argc, char **argv)
{
	char *line;
	int	nbr;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell:");
		if (line[0] == '\0')
			continue ;
		add_history(line);
		nbr = countnbr(line);
		cutline(line, nbr);
		free(line);
	}
}
t_cmd *cmd