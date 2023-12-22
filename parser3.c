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
		if (strncmp(dta->newenv[j], tab, ft_strlen(tab)) == 0)
		{
			tab = dta->newenv[j] + (ft_strlen(tab) + 1);
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
	tmp = ft_calloc(10, sizeof(char));
	tmp = ft_itoa(dta->ext_val);
	while (tmp[k])
		tab[(*j)++] = tmp[k++];
	(*i) += k;
	return (tab);
}

char	*replace_var(t_dta *dta, char *line, int *i)
{
	char	*tab;
	int		j;

	j = 0;
	tab = ft_calloc(dta->len, sizeof(char));
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
		ft_pipes(dta, i);
	else if (line[(*i)] == '<' || line[(*i)] == '>')
		ft_chevron(dta, line, i);
	else if (line[(*i)] != ' ')
		ft_word(dta, line, i);
	return (dta->str);
}

int	check_redir(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (-1);
	while (tab[i])
	{
		if (ft_check_chevron(tab[i]) == 0)
		{
			if (!tab[i + 1])
				return (-1);
		}
		i++;
	}
	return (0);
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
	dta->tab[j] = NULL;
	if (check_redir(dta->tab) == -1)
	{
		printf("syntax error near unexpected token `newline'\n");
		free_string_array(dta->tab, 3);
		return (-1);
	}
	return (0);
}
