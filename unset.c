/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:51:23 by scarpent          #+#    #+#             */
/*   Updated: 2023/11/17 13:51:25 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_linecpy(char *src)
{
	int		i;
	char	*dest;

	i = -1;
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

int	ft_unset_input(char *linesplit)
{
	int	i;

	i = 0;
	while (linesplit[i])
	{
		if (ft_invalid(linesplit[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				linesplit);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_newenv(t_dta *dta, t_cmd *cmd, int i, int j)
{
	int		x;
	char	**oldenv;

	x = 0;
	oldenv = malloc(sizeof(char *) * (ft_tablen(dta->newenv) + 1));
	while (dta->newenv[++i])
	{
		if (!ft_strncmp(dta->newenv[i], cmd->arg[j],
				ft_strlen(cmd->arg[j])))
			i++;
		oldenv[x++] = ft_linecpy(dta->newenv[i]);
	}
	oldenv[x] = NULL;
	return (oldenv);
}

int	ft_unset(t_dta *dta, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**oldenv;

	j = -1;
	while (cmd->arg[++j])
	{
		i = -1;
		if (ft_unset_input(cmd->arg[j]))
			continue ;
		if (j >= ft_tablen(cmd->arg))
			return (1);
		if (!ft_strncmp(cmd->arg[j], dta->newenv[ft_tablen(dta->newenv) - 1], ft_strlen(cmd->arg[j])))
		{
			dta->newenv[ft_tablen(dta->newenv) - 1] = NULL;
			continue ;
		}
		oldenv = ft_newenv(dta, cmd, i, j);
		while (dta->newenv[++i])
			free(dta->newenv[i]);
		free(dta->newenv);
		dta->newenv = oldenv;
	}
	return (0);
}
