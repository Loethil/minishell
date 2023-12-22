/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:13:12 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/12 16:13:15 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_explen(char **tab)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tab[++i])
		j += ft_strlen(tab[i]);
	return (j);
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
