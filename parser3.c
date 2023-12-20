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
	char	*tmp;
	int		j = 0;
	int		k = 0;

	j = 0;
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
		if (line[(*i)] == '?')
		{
			tmp = ft_calloc(10, sizeof(char));
			tmp = ft_itoa(dta->ext_val);
			while (tmp[k])
				tab[j++] = tmp[k++];
			(*i) += k;
			return (tab);
		}
		tab[j++] = line[(*i)++];
	}
	// bug avec simple dans double
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
//faire en sorte que la fonction puisse arreter
//le processus sans fermer minishell et afficher un msg d'erreur

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
		ft_pipes(dta, i);
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
		// free(dta->str);
		j++;
	}
	dta->tab[j] = NULL;
}
