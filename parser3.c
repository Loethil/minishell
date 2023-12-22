/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:40:03 by mbatteux          #+#    #+#             */
/*   Updated: 2023/12/02 15:40:05 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*replace_mac(t_dta *dta, char *tab)
{
	int	j;

	j = 0;
	while (dta->newenv[j])
	{
		if (ft_strncmp(dta->newenv[j], tab, ft_strlen(tab)) == 0)
		{
			tab = ft_strcpy(tab, dta->newenv[j] + (ft_strlen(tab) + 1));
			break ;
		}
		j++;
	}
	if (dta->newenv[j] == NULL)
		return (NULL);
	return (tab);
}

char	*replace_inter(t_dta *dta, char *tab, int *i, int *j)
{
	char	*tmp;
	int		k;

	k = 0;
	tmp = ft_itoa(dta->ext_val);
	while (tmp[k])
		tab[(*j)++] = tmp[k++];
	(*i) += k;
	free(tmp);
	return (tab);
}

char	*replace_var(t_dta *dta, char *line, int *i)
{
	char	*tab;
	int		j;

	j = 0;
	tab = ft_calloc(dta->len + 100, sizeof(char));
	while (line[++(*i)] != '$' && (*i) < dta->len)
	{
		if (line[(*i)] == '|' || line[(*i)] == ' ')
			break ;
		if (line[(*i)] == '"' || line[(*i)] == '\'' )
			break ;
		if (line[(*i)] == '?')
		{
			replace_inter(dta, tab, i, &j);
			return (tab);
		}
		tab[j++] = line[(*i)];
	}
	tab = replace_mac(dta, tab);
	if (tab == NULL)
		return (NULL);
	return (tab);
}

char	*ft_getstr(t_dta *dta, char *line, int *i)
{
	dta->str = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	dta->len = ft_strlen(line);
	if ((*i) >= dta->len)
		return (NULL);
	while (line[(*i)] == ' ')
		(*i)++;
	if (line[(*i)] == '"')
		ft_cpy_dquotes(dta, line, i);
	else if (line[(*i)] == '\'')
		ft_cpy_squotes(dta, line, i);
	else if (line[(*i)] == '|')
		ft_pipes(dta, line, i);
	else if (line[(*i)] == '<' || line[(*i)] == '>')
		ft_chevron(dta, line, i);
	else if (line[(*i)] != ' ')
		ft_word(dta, line, i);
	return (dta->str);
}

int	ft_create_tab(t_dta *dta, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	dta->tab = ft_calloc (dta->nbr + 1, sizeof(char *));
	while (i < dta->len)
	{
		dta->tab[j] = ft_getstr(dta, line, &i);
		j++;
	}
	if (check_redir(dta->tab) == -1)
	{
		printf("syntax error near unexpected token `newline'\n");
		ft_free_tab(dta->tab);
		return (-1);
	}
	return (0);
}
