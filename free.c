/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:11:11 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/19 14:11:12 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (i < ft_tablen(tab) - 1)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_destroy(t_dta *dta)
{
	free(dta->var);
	free(dta->pwd);
	free(dta->buf);
	free(dta->line);
	free(dta->str);
}
