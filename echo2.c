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

void	ft_var_alloc(t_dta *dta, char *cmd, int i)
{
	int	j;

	j = 0;
	dta->var = ft_calloc(ft_strlen(cmd), sizeof(char));
	while (cmd[i])
		dta->var[j++] = cmd[i++];
}

void	ft_print_var(t_dta *dta)
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
				printf("\n");
				return ;
			}
			while (dta->newenv[i][j] && dta->newenv[i][j] != '\n')
				printf("%c", dta->newenv[i][j++]);
		}
	}
}

int	ft_var_hdl(t_dta *dta, char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '$' && i == 0)
		{
			i++;
			ft_var_alloc(dta, cmd, i);
			return (1);
		}
		else if (cmd[i] == '$' && i)
		{
			i = 0;
			while (cmd[i] != '$')
				printf("%c", cmd[i++]);
			i++;
			ft_var_alloc(dta, cmd, i);
			return (1);
		}
	}
	return (0);
}
