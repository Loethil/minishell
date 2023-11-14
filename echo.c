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

int	ft_echo(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (strncmp(data->linesplit[1], "-n", 2) == 0)
	{
		while (strncmp(data->linesplit[i], "-n", 2) == 0)
		{
			while (data->linesplit[i][j] == 'n')
				j++;
			i++;
		}
		while (data->linesplit[i])
		{
			if (ft_tablen(data->linesplit) < 3 || i == ft_tablen(data->linesplit) - 1)
				printf("%s", data->linesplit[i]);
			else
				printf("%s ", data->linesplit[i]);
			i++;	
		}
	}
	else
	{
		while (data->linesplit[i])
		{
			if (ft_tablen(data->linesplit) < 3 || i == ft_tablen(data->linesplit) - 1)
				printf("%s\n", data->linesplit[i]);
			else
				printf("%s ", data->linesplit[i]);
			i++;
		}
	}
	return (0);
}
