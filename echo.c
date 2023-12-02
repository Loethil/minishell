/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:00:54 by scarpent          #+#    #+#             */
/*   Updated: 2023/11/14 12:00:55 by scarpent         ###   ########.fr       */
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

void	ft_print_echo(char **linesplit, int i)
{
	while (linesplit[i])
	{
		if (ft_tablen(linesplit) <= 2 || i == ft_tablen(linesplit) - 1)
			printf("%s", linesplit[i]);
		else
			printf("%s ", linesplit[i]);
		i++;
	}
}

int	ft_echo(t_data *data, int i)
{
	int	j;

	if (strncmp(data->linesplit[1], "-n", 2) == 0)
	{
		while (strncmp(data->linesplit[i], "-n", 2) == 0)
		{
			j = 1;
			while (data->linesplit[i][j] == 'n')
				j++;
			if (data->linesplit[i][j])
			{
				ft_print_echo(data->linesplit, i);
				return (0);
			}
			i++;
		}
		ft_print_echo(data->linesplit, i);
	}
	else
	{
		ft_print_echo(data->linesplit, i);
		printf("\n");
	}
	return (0);
}
