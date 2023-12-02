/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:41:50 by scarpent          #+#    #+#             */
/*   Updated: 2023/11/15 14:43:06 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_invalid(char i)
{
	if (i == '$' || i == '%' || i == '!'
		|| i == '+' || i == ',' || i == ','
		|| i == '-' || i == '.' || i == '?'
		|| i == '/' || i == '[' || i == ']'
		|| i == '{' || i == '}' || i == '~'
		|| i == '*' || i == '#' || i == '&'
		|| i == '(' || i == ')' || i == ':'
		|| i == ';' || i == '\\'
		|| (i >= '0' && i <= '9'))
		return (1);
	return (0);
}

int	ft_export_input(char *linesplit)
{
	int	i;

	i = 0;
	while (linesplit[i] && linesplit[i] != '=')
	{
		if (ft_invalid(linesplit[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				linesplit);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export_malloc(t_dta *dta, int i, int k)
{
	dta->newenv[i] = malloc(sizeof(char)
			* (ft_strlen(dta->linesplit[k]) + 1));
	ft_strcpy(dta->newenv[i], dta->linesplit[k]);
}

int	ft_sub_export(t_dta *dta, int i, int k)
{
	int	j;

	j = 0;
	if (dta->linesplit[k][0] == '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n",
			dta->linesplit[k]);
		return (++k);
	}
	while (dta->linesplit[k][j] && dta->linesplit[k][j] != '=')
		j++;
	if (ft_strncmp(dta->newenv[i], dta->linesplit[k], j) == 0)
	{
		free(dta->newenv[i]);
		ft_export_malloc(dta, i, k);
		i = 0;
		k++;
	}
	return (k);
}

int	ft_export(t_dta *dta)
{
	int	i;
	int	k;

	k = 0;
	if (!dta->linesplit[1])
	{
		ft_export_no_args(dta);
		return (0);
	}
	while (dta->linesplit[++k])
	{
		i = -1;
		while (dta->newenv[++i])
		{
			if (k < ft_sub_export(dta, i, k))
			{
				k++;
				i = -1;
			}
			if (k >= ft_tablen(dta->linesplit))
				return (1);
		}
		if (i == ft_tablen(dta->newenv) && !ft_export_input(dta->linesplit[k])
			&& ft_strchr(dta->linesplit[k], '='))
			ft_export_malloc(dta, i, k);
	}
	return (0);
}
