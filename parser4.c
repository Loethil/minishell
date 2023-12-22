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

void	ft_pipes(t_dta *dta, char *line, int *i)
{
	dta->str[ft_strlen(dta->str)] = line[(*i)];
	(*i)++;
}

void	ft_cpy_squotes(t_dta *dta, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[(*i)] == '\'')
	{
		dta->str[j++] = line[(*i)];
		while (line[++(*i)] != '\'' && (*i) < dta->len)
			dta->str[j++] = line[(*i)];
		if ((*i) >= dta->len)
			return ;
		dta->str[j++] = line[(*i)];
	}
	(*i)++;
}

void	ft_cpy_dquotes(t_dta *dta, char *line, int *i)
{
	if (line[(*i)] == '"')
	{
		dta->str[ft_strlen(dta->str)] = line[(*i)];
		(*i)++;
		while (line[(*i)] != '"' && (*i) < dta->len)
		{
			if (line[(*i)] == '$')
			{
				ft_dollar(dta, line, i);
				continue ;
			}
			dta->str[ft_strlen(dta->str)] = line[(*i)++];
		}
		dta->str[ft_strlen(dta->str)] = line[(*i)];
	}
	(*i)++;
}

int	ft_chevron(t_dta *dta, char *line, int *i)
{
	if (line[(*i)] == '<' && line[(*i) + 1] == '<')
	{
		dta->str[ft_strlen(dta->str)] = line[(*i)];
		dta->str[ft_strlen(dta->str)] = line[(*i) + 1];
		(*i) += 2;
		return (1);
	}
	else if (line[(*i)] == '>' && line[(*i) + 1] == '>')
	{
		dta->str[ft_strlen(dta->str)] = line[(*i)];
		dta->str[ft_strlen(dta->str)] = line[(*i) + 1];
		(*i) += 2;
		return (1);
	}
	else if (line[(*i)] == '<')
	{
		dta->str[ft_strlen(dta->str)] = line[(*i)++];
		return (1);
	}
	else if (line[(*i)] == '>')
	{
		dta->str[ft_strlen(dta->str)] = line[(*i)++];
		return (1);
	}
	return (0);
}

void	ft_word(t_dta *dta, char *line, int *i)
{
	while ((*i) < dta->len)
	{
		if (line[(*i)] == '|')
		{
			dta->str[ft_strlen(dta->str)] = '\0';
			return ;
		}
		if (line[(*i)] == ' ')
			break ;
		if (line[(*i)] == '$')
		{
			ft_dollar(dta, line, i);
			continue ;
		}
		if (line[(*i)] == '"')
			ft_cpy_dquotes2(dta, line, i);
		if (line[(*i)] == '\'')
			ft_cpy_squotes2(dta, line, i);
		dta->str[ft_strlen(dta->str)] = line[(*i)++];
	}
	(*i)++;
}
