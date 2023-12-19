/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:37:30 by mbatteux          #+#    #+#             */
/*   Updated: 2023/12/02 15:37:33 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_check_quotes(t_dta *dta, char *str, int *i)
{
	if (str[(*i)] == '\'')
	{
		while (str[++(*i)] != '\'' && (*i) < dta->len)
			;
		if (str[*i] != '\'' && (*i) == dta->len)
			return (-1);
		dta->nbr++;
	}
	else if (str[(*i)] == '"')
	{
		while (str[++(*i)] != '"' && (*i) < dta->len)
			;
		if (str[*i] != '"' && (*i) == dta->len)
			return (-1);
		dta->nbr++;
	}
	return (0);
}

int	ft_check_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd) - 1;
	if (ft_strncmp(cmd, "echo", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", len) == 0)
		return (1);
	return (0);
}

int	ft_check_word(t_dta *dta, char *str, int *i)
{
	while (str[(*i)] != ' ' && (*i) < dta->len)
	{
		if (str[(*i)] == '|')
		{
			if (str[(*i) + 1] == '|')
				return (-2);
			if (str[(*i) + 1] == '\0')
				return (-2);
			dta->pnbr++;
			dta->nbr += 2;
		}
		(*i)++;
	}
	dta->nbr++;
	return (0);
}

int	ft_countword(t_dta *dta, char *str)
{
	int	i;

	i = -1;
	dta->pnbr = 1;
	dta->nbr = 0;
	dta->len = ft_strlen(str);
	while (++i < dta->len)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (ft_check_quotes(dta, str, &i) == -1)
				return (-1);
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] == '|' || str[i + 1] == '\0')
				return (-2);
			dta->pnbr++;
			dta->nbr++;
		}
		else if (str[i] != ' ')
			if (ft_check_word(dta, str, &i) == -2)
				return (-2);
	}
	return (0);
}

int	ft_check_chevron(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (0);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (0);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (0);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (0);
	return (1);
}
