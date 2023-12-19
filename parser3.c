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

int	ft_check_word(t_dta *dta, char *str, int *i)
{
	while (str[(*i)] != ' ' && (*i) < dta->len)
	{
		if (str[(*i)] == '|')
		{
			if (str[(*i) + 1] == '|')
				return (-2);
			if (str[(*i) + 1] == '\0')
				return (-2);
			dta->pnbr++;
			dta->nbr += 2;
		}
		(*i)++;
	}
	dta->nbr++;
	return (0);
}

int	ft_countword(t_dta *dta, char *str)
{
	int	i;

	i = -1;
	dta->pnbr = 1;
	dta->nbr = 0;
	dta->len = ft_strlen(str);
	while (++i < dta->len)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (ft_check_quotes(dta, str, &i) == -1)
				return (-1);
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] == '|' || str[i + 1] == '\0')
				return (-2);
			dta->pnbr++;
			dta->nbr++;
		}
		else if (str[i] != ' ')
			if (ft_check_word(dta, str, &i) == -2)
				return (-2);
	}
	return (0);
}

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


char	*replace_var(t_dta *dta, char *line, int *i)
{
	char	*tab;
	int		j = 0;

	tab = ft_calloc(dta->len, sizeof(char));
	while (line[(*i)] == '$')
		(*i)++;
	while (line[(*i)] != '$' && (*i) < dta->len)
	{
		if (line[(*i)] == '|')
			break ;
		if (line[(*i)] == ' ')
			break ;
		if (line[(*i)] == '"')
			break ;
		tab[j++] = line[(*i)++];
	} // bug avec simple dans double
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
	// printf("%s\n", tab);	
	return (tab);
}
//faire en sorte que la fonction puisse arreter le processus sans fermer minishell et afficher un msg d'erreur

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
			tab =  replace_var(dta, line, i);
			dta->str = ft_freestrjoin(dta->str, tab);
			continue ;
		}
		dta->str[(*j)++] = line[(*i)++];
	}
	(*i)++;
}

char	*ft_getstr(t_dta *dta, char *line, int *i)
{
	int	j;

	j = 0;
	dta->str = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	dta->len = ft_strlen(line);
	if ((*i) >= dta->len)
		return (NULL);
	while (line[(*i)] == ' ')
		(*i)++;
	if (line[(*i)] == '"' || line[(*i)] == '\'')
		ft_cpy_quotes(dta, line, i);
	else if (line[(*i)] == '|')
		ft_pipes(dta, line, i);
	else if (line[(*i)] == '<' || line[(*i)] == '>')
		ft_chevron(dta, line, i);
	else if (line[(*i)] != ' ')
		ft_word(dta, line, i, &j);
	return (dta->str);
}

void	ft_create_tab(t_dta *dta, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	dta->tab = ft_calloc (dta->nbr + 1, sizeof(char *));
	while (i < dta->len)
	{
		dta->tab[j] = ft_getstr(dta, line, &i);
		// printf("%s\n", dta->tab[j]);
		j++;
	}
	dta->tab[j] = NULL;
}
