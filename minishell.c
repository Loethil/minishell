/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:45:59 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/07 14:38:40 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint = 0;

void	ft_exit(t_dta *dta, t_cmd *cmd)
{
	char	*chk;

	printf ("exit\n");
	if (cmd->arg[0] == NULL)
		exit (0);
	dta->ext = ft_atoll(cmd->arg[0]);
	chk = ft_itoa(dta->ext);
	if (ft_strcmp(cmd->arg[0], chk) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->arg[0]);
		exit (2);
	}
	dta->ext %= 256;
	if (cmd->arg[1])
	{
		printf("minishell: exit: too many arguments\n");
		dta->ext_val = 1;
		return ;
	}
	exit(dta->ext);
}

int	ft_whoitis(t_dta *dta, t_cmd *cmd)
{
	int	len;

	dta->res = -1;
	len = ft_strlen(cmd->cmd[0]);
	if (ft_strncmp(cmd->cmd[0], "echo", len) == 0)
		ft_echo(dta, cmd, 0);
	else if (ft_strncmp(cmd->cmd[0], "cd", len) == 0)
	{
		if (cmd->arg[1])
		{
			printf("minishell: cd: too many arguments\n");
			return (-1);
		}
		ft_changedir(dta, cmd->arg[0]);
	}
	else if (ft_strncmp(cmd->cmd[0], "pwd", len) == 0)
		ft_pwdorenv(dta, dta->newenv, "PWD");
	else if (ft_strncmp(cmd->cmd[0], "export", len) == 0)
		ft_export(dta, cmd);
	else if (ft_strncmp(cmd->cmd[0], "unset", len) == 0)
		ft_unset(dta, cmd);
	else if (ft_strncmp(cmd->cmd[0], "env", len) == 0)
		ft_pwdorenv(dta, dta->newenv, "ENV");
	else if (ft_strncmp(cmd->cmd[0], "exit", len) == 0)
		ft_exit(dta, cmd); // a corriger
	return (dta->res);
}

int	main(int argc, char **argv, char **env)
{
	t_dta	*dta;
	int		i;

	(void)argv;
	dta = ft_calloc (1, sizeof(t_dta));
	i = -1;
	if (argc != 1)
		return (0);
	dta->newenv = changeenv(dta, env);
	dta->ext_val = 0;
	signal(SIGINT, &ft_sigint_hdl);
	ft_prompt(dta);
	return (0);
}
