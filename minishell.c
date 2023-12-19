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

int	ft_whoitis(t_dta *dta, t_cmd *cmd)
{
	int	len;

	dta->res = -1;
	len = ft_strlen(cmd->cmd[0]);
	if (ft_strncmp(cmd->cmd[0], "echo", len) == 0)
		ft_echo(dta, cmd, 0);
	else if (ft_strncmp(cmd->cmd[0], "cd", len) == 0)
		ft_changedir(dta, cmd->arg[0]);
	else if (ft_strncmp(cmd->cmd[0], "pwd", len) == 0)
		ft_pwdorenv(dta, dta->newenv, "PWD");
	else if (ft_strncmp(cmd->cmd[0], "export", len) == 0)
		ft_export(dta, cmd);
	else if (ft_strncmp(cmd->cmd[0], "unset", len) == 0)
		ft_unset(dta, cmd);
	else if (ft_strncmp(cmd->cmd[0], "env", len) == 0)
		ft_pwdorenv(dta, dta->newenv, "ENV");
	else if (ft_strncmp(cmd->cmd[0], "exit", len) == 0)
		ft_exit(dta, cmd);
	return (dta->res);
}

void	ft_set_up(t_dta *dta, char *line)
{
	t_cmd	*cmd;

	if (ft_check_line(dta, line) == -1)
		return ;
	dta->var = NULL;
	cmd = ft_calloc(dta->pnbr + 1, sizeof(t_cmd));
	ft_create_tab(dta, line);
	ft_cmd_init(dta, cmd, dta->tab);
	ft_pars(cmd, dta->tab);
	if (dta->pnbr == 1 && ft_check_builtin(cmd->cmd[0]) == 1)
		if (ft_cmd_simple(dta, cmd) == 0)
			return ;
	ft_pipex(dta, cmd);
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
	signal(SIGQUIT, &ft_sigquit_hdl);
	ft_prompt(dta);
	free(dta);
	return (0);
}
