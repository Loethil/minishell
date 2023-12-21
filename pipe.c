/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:57:07 by mbatteux          #+#    #+#             */
/*   Updated: 2023/12/06 13:57:08 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	first_proc(t_dta *dta, t_cmd *cmd, int pipe_fd[2])
{
	if (dta->pnbr != 1)
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_error(cmd, dta, "error");
	if (ft_redirect(dta, cmd) == 1)
		exit (0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (ft_whoitis(dta, cmd) == 0)
		exit (0);
	if (execve(cmd->tpath, cmd->lne, dta->newenv) == -1)
		ft_error(cmd, dta, "error");
}

void	middle_proc(t_dta *dta, t_cmd *cmd, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (ft_redirect(dta, cmd) == 1)
		exit (0);
	if (cmd->in_fd == STDIN_FILENO)
		if (dup2(cmd->pfd, cmd->in_fd) == -1)
			ft_error(cmd, dta, "error");
	if (cmd->out_fd == STDOUT_FILENO)
		if (dup2(pipe_fd[1], cmd->out_fd) == -1)
			ft_error(cmd, dta, "error");
	close(pipe_fd[1]);
	if (ft_whoitis(dta, cmd) == 0)
		exit (0);
	if (execve(cmd->tpath, cmd->lne, dta->newenv) == -1)
		ft_error(cmd, dta, "error");
}

void	final_proc(t_dta *dta, t_cmd *cmd, int pipe_fd[2])
{
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (ft_redirect(dta, cmd) == 1)
		exit (0);
	if (cmd->in_fd == STDIN_FILENO)
		if (dup2(cmd->pfd, STDIN_FILENO) == -1)
			ft_error(cmd, dta, "error");
	if (ft_whoitis(dta, cmd) == 0)
		exit (0);
	if (execve(cmd->tpath, cmd->lne, dta->newenv) == -1)
		ft_error(cmd, dta, "error");
}

void	choose_proc(t_dta *dta, t_cmd *cmd, int pipe_fd[2], int *j)
{
	if (cmd[(*j)].pid == 0)
	{
		if ((*j) == 0)
			first_proc(dta, &cmd[(*j)], pipe_fd);
		else if ((*j) == dta->pnbr - 1)
			final_proc(dta, &cmd[(*j)], pipe_fd);
		else
			middle_proc(dta, &cmd[(*j)], pipe_fd);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(cmd[(*j)].pid, &dta->status, 0);
		(*j)++;
		cmd[(*j)].pfd = pipe_fd[0];
	}
}

void	ft_pipex(t_dta *dta, t_cmd *cmd)
{
	int	j;
	int	pipe_fd[2];

	j = 0;
	ft_set_cmd(dta, cmd);
	while (j < dta->pnbr)
	{
		if (pipe(pipe_fd) == -1)
			ft_error(cmd, dta, "error");
		cmd[j].pid = fork();
		if (cmd[j].pid == -1)
			ft_error(cmd, dta, "error");
		if (cmd[j].pid == 0)
			choose_proc(dta, cmd, pipe_fd, &j);
		else
		{
			close(pipe_fd[1]);
			waitpid(cmd[j].pid, &dta->status, 0);
			if (WIFEXITED(dta->status) && WEXITSTATUS(dta->status))
                dta->ext_val = 127;
			j++;
			cmd[j].pfd = pipe_fd[0];
		}
	}
}
