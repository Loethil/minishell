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

void	ft_export_malloc(t_data *data, int i)
{
	data->newenv[i] = malloc(sizeof(char)
			* (ft_strlen(data->linesplit[1]) + 1));
	ft_strcpy(data->newenv[i], data->linesplit[1]);
}

int	ft_export(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strchr(data->linesplit[1], '=') == 0)
		return (1);
	while (data->newenv[i])
	{
		j = 0;
		while (data->newenv[i][j - 1] != '=' && data->newenv[i][j])
			j++;
		if (ft_strncmp(data->newenv[i], data->linesplit[1], j) == 0)
		{
			free(data->newenv[i]);
			ft_export_malloc(data, i);
			return (0);
		}
		i++;
	}
	if (i == ft_tablen(data->newenv))
		ft_export_malloc(data, i);
	return (0);
}
