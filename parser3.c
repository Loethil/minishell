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

int	ft_countword(t_dta *dta, char *str)
{
	int	i;
	int	j;
	int	lmax;

	i = 0;
	j = 0;
	dta->pnbr = 1;
	lmax = ft_strlen(str);
	while (i < lmax)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			j = ft_check_quotes(str, &i, j, lmax);
			if (j == -1)
				return (-1);
		}
		else if (str[i] == '|')
		{
			dta->pnbr++;
			j++;
		}
		else if (str[i] != ' ')
		{
			while (str[i] != ' ' && i < lmax)
			{
				if (str[i] == '|')
				{
					dta->pnbr++;
					j += 2;
				}
				i++;
			}
			j++;
		}
		i++;
	}
	return (j);
} // a reduire norminette

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

	tab = ft_calloc(ft_strlen(line), sizeof(char));
	while (line[(*i)] == '$')
		(*i)++;
	while (line[(*i)] != '$' && (*i) < dta->lmax)
	{
		if (line[(*i)] == '|')
			break ;
		if (line[(*i)] == ' ')
			break ;
		if (line[(*i)] == '"')
			break ;
		tab[j++] = line[(*i)++];
	}
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

	while ((*i) < dta->lmax)
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
	dta->lmax = ft_strlen(line);
	if ((*i) >= dta->lmax)
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
	while (j < dta->nbr)
	{
		dta->tab[j] = ft_getstr(dta, line, &i);
		printf("%s\n", dta->tab[j]);
		j++;
	}
	dta->tab[j] = NULL;
}
