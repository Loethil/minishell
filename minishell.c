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

t_sig	g_sig;

void	ft_exit(t_dta *dta, t_cmd *cmd)
{
	char	*chk; // check

	printf ("exit\n");
	if (cmd->arg[0] == NULL)
		exit (0);
	dta->ext = ft_atoll(cmd->arg[0]);
	chk = ft_itoa(dta->ext);
	if (strcmp(cmd->arg[0], chk) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->arg[0]);
		exit (2);
	}
	dta->ext %= 256;
	if (cmd->arg[1])
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	exit(dta->ext);
}

void	ft_findcmd(t_dta *dta, t_cmd *cmd)
{
	dta->pid = fork();
	if (dta->pid == 0)
	{
		dta->all_path = ft_find_path(dta);
		dta->true_path = ft_get_access(dta, cmd->cmd[0]);
		if (execve(dta->true_path,  &cmd->cmd[0], dta->newenv) == -1)
			printf("error execve\n");
	}
	else
		waitpid(dta->pid, &dta->status, 0);
}

void	ft_whoitis(t_dta *dta, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		ft_echo(dta, cmd, 0);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		ft_changedir(dta, cmd->arg[0]);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		ft_pwdorenv(dta->newenv, "PWD");
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		ft_export(dta, cmd);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		ft_unset(dta, cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		ft_pwdorenv(dta->newenv, "ENV");
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		ft_exit(dta, cmd);
	else
		ft_findcmd(dta, cmd);
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
	signal(SIGINT, &ft_sigint_hdl);
	signal(SIGQUIT, &ft_sigquit_hdl);
	ft_prompt(dta);
	return (0);
}
