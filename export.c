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

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(src);
	j = -1;
	while (++j < i + 1)
		dst[j] = src[j];
	dst[j] = '\0';
	return (dst);
}

int	ft_export_input(char *linesplit)
{
	int	i;

	i = 0;
	if (linesplit[i] == '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n", linesplit);
		return (1);
	}
	while (linesplit[i] && linesplit[i] != '=')
	{
		if (ft_isalpha(linesplit[i]) == 0)
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

int	ft_check(t_data *data, int k)
{
	if (ft_export_input(data->linesplit[k])
		|| ft_strchr(data->linesplit[k], '=') == 0)
	{
		if (!data->linesplit[k + 1])
			return (1);
		k++;
	}
	return (k);
}

int	ft_export(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 1;
	while (data->newenv[i] && data->linesplit[k])
	{
		k = ft_check(data, k);
		j = 0;
		while (data->newenv[i][j - 1] != '=' && data->newenv[i][j])
			j++;
		if (ft_strncmp(data->newenv[i], data->linesplit[k], j) == 0)
		{
			free(data->newenv[i]);
			ft_export_malloc(data, i, k);
			i = 0;
			k++;
		}
		i++;
	}
	if (i == ft_tablen(data->newenv))
		ft_export_malloc(data, i, k);
	return (0);
}
