/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:07:17 by scarpent          #+#    #+#             */
/*   Updated: 2023/11/23 15:07:18 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_whitespace(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (i != ft_strlen(line))
		return (0);
	return (1);
}

void	ft_prompt(t_data *data)
{
	while (1)
	{
		data->line = readline("minishell: ");
		if (data->line == NULL)
		{
			printf("exit\n");
			return ;
		}
		if (data->line[0] == '\0' || ft_whitespace(data->line))
			continue ;
		if (sig.sigint == 1)
		{
			sig.sigint = 0;
			free(data->line);
			data->line[0] = '\0';
			continue ;
		}
		add_history(data->line);
		data->linesplit = ft_split(data->line, ' ');
		ft_whoitis(data);
	}
}
