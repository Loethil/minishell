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

void	ft_export_malloc(t_data *data, int i, int k)
{
	data->newenv[i] = malloc(sizeof(char)
			* (ft_strlen(data->linesplit[k]) + 1));
	ft_strcpy(data->newenv[i], data->linesplit[k]);
}

int	ft_sub_export(t_data *data, int i, int k)
{
	int	j;

	j = 0;
	if (data->linesplit[k][0] == '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n",
			data->linesplit[k]);
		return (++k);
	}
	while (data->linesplit[k][j] && data->linesplit[k][j] != '=')
		j++;
	if (ft_strncmp(data->newenv[i], data->linesplit[k], j) == 0)
	{
		free(data->newenv[i]);
		ft_export_malloc(data, i, k);
		i = 0;
		k++;
	}
	return (k);
}

int	ft_export(t_data *data)
{
	int	i;
	int	k;

	k = 0;
	if (!data->linesplit[1])
	{
		ft_export_no_args(data);
		return (0);
	}
	while (data->linesplit[++k])
	{
		i = -1;
		while (data->newenv[++i])
		{
			if (k < ft_sub_export(data, i, k))
			{
				k++;
				i = -1;
			}
			if (k >= ft_tablen(data->linesplit))
				return (1);
		}
		if (i == ft_tablen(data->newenv) && !ft_export_input(data->linesplit[k])
			&& ft_strchr(data->linesplit[k], '='))
			ft_export_malloc(data, i, k);
	}
	return (0);
}
