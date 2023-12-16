/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:41:33 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/06 13:41:36 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_var_hdl(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '$')
			return (1);
	}
	return (0);
}

void	ft_var_alloc(t_dta *dta, char *arg, int i)
{
	int	j;

	j = 0;
	dta->var = ft_calloc(ft_strlen(arg), sizeof(char));
	while (arg[i] && arg[i] != '$')
		dta->var[j++] = arg[i++];
}

void	ft_print_var(t_dta *dta, int *k)
{
	int	i;
	int	j;

	i = -1;
	while (dta->newenv[++i])
	{
		if (ft_strncmp(dta->newenv[i], dta->var, ft_strlen(dta->var)) == 0)
		{
			j = 0;
			while (dta->newenv[i][j] != '=')
				j++;
			if (dta->newenv[i][j] == '=' && dta->newenv[i][j])
				j++;
			else
			{
				return ;
			}
			while (dta->newenv[i][j] && dta->newenv[i][j] != '\n')
				dta->str[(*k)++] = dta->newenv[i][j++];
		}
	}
}

char	*ft_var(char *arg, t_dta *dta, int *j)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			printf("%d", dta->ext_val);
			i++;
			continue ;
		}
		else if (arg[i] == '$' && arg[i + 1])
		{
			i++;
			ft_var_alloc(dta, arg, i);
			ft_print_var(dta, j);
			i += ft_strlen(dta->var) - 1;
			continue ;
		}
		dta->str[(*j)++] = arg[i];
		dta->str[(*j)] = '\0';
	}
	return (dta->str);
}

void	ft_var_master(char **arg, t_dta *dta, int i)
{
	if (ft_tablen(arg) < 2 || i == ft_tablen(arg) - 1)
	{
		ft_var(arg[i], dta, &i);
		return ;
	}
	else
	{
		ft_var(arg[i], dta, &i);
		printf(" ");
	}
}
