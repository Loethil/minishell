/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:30:45 by mbatteux          #+#    #+#             */
/*   Updated: 2023/12/22 16:30:48 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_freestrjoin(char *s1, char *s2)
{
	char	*tab;
	int		r;
	int		a;

	tab = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	r = 0;
	a = 0;
	while (s1 && s1[r])
	{
		tab[r] = s1[r];
		r++;
	}
	while (s2 && s2[a])
		tab[r++] = s2[a++];
	tab[r] = '\0';
	free(s1);
	return (tab);
}

char	*ft_dollar(t_dta *dta, char *line, char *tab, int *i)
{
	if (ft_isalpha(line[(*i) + 1]) == 0)
	{
		dta->str = ft_freestrjoin(dta->str, "$");
		(*i)++;
		return (tab);
	}
	tab = replace_var(dta, line, i);
	dta->str = ft_freestrjoin(dta->str, tab);
	return (tab);
}

int	ft_word_and_quotes(t_dta *dta, char *line, int *i)
{
	if (line[(*i)] == '"')
	{
		(*i)++;
		if (line[(*i)] == '\'')
		{
			dta->str[ft_strlen(dta->str)] = line[(*i)++];
			while (line[(*i)] != '\'' && (*i) < dta->len)
				dta->str[ft_strlen(dta->str)] = line[(*i)++];
			dta->str[ft_strlen(dta->str)] = line[(*i)++];
		}
		return (1);
	}
	if (line[(*i)] == '\'')
	{
		while (line[++(*i)] != '\'' && (*i) < dta->len)
			dta->str[ft_strlen(dta->str)] = line[(*i)];
		return (1);
	}
	return (0);
}

void	ft_cpy_dquotes2(t_dta *dta, char *line, int *i)
{
	char	*tab;

	if (line[(*i)] == '"')
	{
		(*i)++;
		while (line[(*i)] != '"' && (*i) < dta->len)
		{
			if (line[(*i)] == '$')
			{
				tab = ft_dollar(dta, line, tab, i);
				continue ;
			}
			dta->str[ft_strlen(dta->str)] = line[(*i)++];
		}
	}
	(*i)++;
}

void	ft_cpy_squotes2(t_dta *dta, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[(*i)] == '\'')
	{
		while (line[++(*i)] != '\'' && (*i) < dta->len)
			dta->str[j++] = line[(*i)];
		if ((*i) >= dta->len)
			return ;
	}
}
