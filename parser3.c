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

void	ft_word(t_dta *dta, char *line, int *i, int *j)
{
	while (dta->str[(*i)] != ' ' && (*i) < dta->lmax)
	{
		if (dta->str[(*i)] == '|')
		{
			dta->str[(*j)] = '\0';
			return ;
		}
		dta->str[(*j)++] = line[(*i)++];
	}
	dta->str[(*j)] = '\0';
	(*i)++;
}

char	*ft_getstr(t_dta *dta, char *line, int *i)
{
	int	j;

	j = 0;
	dta->str = ft_copystring(line);
	dta->lmax = ft_strlen(line);
	if ((*i) >= dta->lmax)
		return (NULL);
	while (dta->str[(*i)] == ' ')
		(*i)++;
	if (dta->str[(*i)] == '"' || dta->str[(*i)] == '\'')
		ft_cpy_quotes(dta, line, i);
	else if (dta->str[(*i)] == '|')
		ft_pipes(dta, i);
	else if (dta->str[(*i)] == '<' || dta->str[(*i)] == '>')
		ft_chevron(dta, i);
	else if (dta->str[(*i)] != ' ')
		ft_word(dta, line, i, &j);
	return (dta->str);
}

void	ft_create_tab(t_dta *dta, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	dta->tab = ft_calloc (dta->nbr, sizeof(char *));
	while (j < dta->nbr)
	{
		dta->tab[j] = ft_getstr(dta, line, &i);
		printf("%s\n", dta->tab[j]);
		j++;
	}
	dta->tab[j] = NULL;
}