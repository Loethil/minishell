/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:37:30 by mbatteux          #+#    #+#             */
/*   Updated: 2023/12/02 15:37:33 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_check_quotes(char *str, int *i, int j, int lmax)
{
	if (str[(*i)] == '\'')
	{
		while (str[++(*i)] != '\'' && (*i) < lmax)
			;
		if (str[*i] != '\'' && (*i) == lmax)
			return (-1);
		j++;
	}
	else if (str[(*i)] == '"')
	{
		while (str[++(*i)] != '"' && (*i) < lmax)
			;
		if (str[*i] != '"' && (*i) == lmax)
			return (-1);
		j++;
	}
	return (j);
}

void	ft_pipes(t_dta *dta, char *line, int *i)
{
	if (line[(*i) + 1] == '|')
		return ;
	if (line[(*i)] == '|' && (*i) == dta->lmax)
		return ; //bug avec trop de pipes a regler
	dta->str = "|";
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

void	ft_cpy_quotes(t_dta *dta, char *line, int *i)
{
	int	j;
	char *tab;

	j = 0;
	if (line[(*i)] == '\'')
	{
		while (line[++(*i)] != '\'' && (*i) < dta->lmax)
			dta->str[j++] = line[(*i)];
		dta->str[j] = '\0';
	}
	else if (line[(*i)] == '"')
	{
		while (line[++(*i)] != '"' && (*i) < dta->lmax)
		{
			if (line[(*i)] == '$')
			{
				tab =  replace_var(dta, line, i);
				dta->str = ft_freestrjoin(dta->str, tab);
				continue ;
			}
			dta->str[j++] = line[(*i)];
		}
	}
	(*i)++;
}
