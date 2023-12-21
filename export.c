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
	if (linesplit[0] == '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n", linesplit);
		return (1);
	}
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

void	ft_export_malloc(t_dta *dta, t_cmd *cmd, int i, int k)
{
	dta->newenv[i] = ft_calloc(ft_strlen(cmd->arg[k]), sizeof(char));
	ft_strcpy(dta->newenv[i], cmd->arg[k]);
}

int	ft_sub_export(t_dta *dta, t_cmd *cmd, int i, int k)
{
	int	j;

	j = 0;
	if (!cmd->arg[k])
		return (ft_tablen(cmd->arg));
	if (!ft_strchr(cmd->arg[k], '='))
		return (k + 1);
	while (cmd->arg[k][j] && cmd->arg[k][j] != '=')
		j++;
	if (dta->newenv[i] && ft_strncmp(dta->newenv[i], cmd->arg[k], j) == 0)
	{
		ft_export_malloc(dta, cmd, i, k);
		return (k + 1);
	}
	return (k);
}

int	ft_export(t_dta *dta, t_cmd *cmd, int k)
{
	int	i;

	dta->res = 0;
	if (!cmd->arg[0])
		return (ft_export_no_args(dta));
	while (cmd->arg[++k])
	{
		if (k >= ft_tablen(cmd->arg))
			return (dta->res);
		if (ft_export_input(cmd->arg[k]) || !ft_strchr(cmd->arg[k], '='))
			continue ;
		i = -1;
		while (dta->newenv[++i])
		{
			if (k < ft_sub_export(dta, cmd, i, k))
			{
				k++;
				i = -1;
			}
		}
		if (i >= ft_tablen(dta->newenv) && cmd->arg[k])
			ft_export_malloc(dta, cmd, i, k);
		dta->newenv[++i] = NULL;
	}
	return (dta->res);
}
