/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:45:19 by mbatteux          #+#    #+#             */
/*   Updated: 2023/12/19 17:58:34 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipes(t_dta *dta, int *i)
{
	dta->str = "|";
	(*i)++;
}

void	ft_cpy_quotes(t_dta *dta, char *line, int *i)
{
	int		j;
	char	*tab;

	j = 0;
	if (line[(*i)] == '\'')
	{
		while (line[++(*i)] != '\'' && (*i) < dta->len)
			dta->str[j++] = line[(*i)];
		dta->str[j] = '\0';
	}
	else if (line[(*i)] == '"')
	{
		while (line[++(*i)] != '"' && (*i) < dta->len)
		{
			if (line[(*i)] == '$')
			{
				tab = replace_var(dta, line, i);
				dta->str = ft_freestrjoin(dta->str, tab);
				continue ;
			}
			dta->str[j++] = line[(*i)];
		}
	}
	(*i)++;
}

void	ft_chevron(t_dta *dta, char *line, int *i)
{
	if (line[(*i)] == '<' && line[(*i) + 1] == '<')
	{
		dta->str = "<<";
		(*i) += 2;
	}
	else if (line[(*i)] == '>' && line[(*i) + 1] == '>')
	{
		dta->str = ">>";
		(*i) += 2;
	}
	else if (line[(*i)] == '<')
	{
		dta->str = "<";
		(*i)++;
	}
	else if (line[(*i)] == '>')
	{
		dta->str = ">";
		(*i)++;
	}
}

void	ft_word(t_dta *dta, char *line, int *i, int *j)
{
	char	*tab;

	while ((*i) < dta->len)
	{
		if (line[(*i)] == '|')
		{
			dta->str[(*j)] = '\0';
			return ;
		}
		if (line[(*i)] == ' ')
			break ;
		if (line[(*i)] == '$')
		{
			tab = replace_var(dta, line, i);
			dta->str = ft_freestrjoin(dta->str, tab);
			continue ;
		}
		dta->str[(*j)++] = line[(*i)++];
	}
	(*i)++;
}
