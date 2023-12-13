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

void	free_tabs(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	error(t_cmd *cmd, t_dta *dta, char *err)
{
	int	i;

	i = 0;
	while (i < dta->pnbr)
	{
		free_tabs(cmd[i].lne);
		free_tabs(cmd[i].cmd);
		free_tabs(cmd[i].arg);
		i++;
	}
	perror (err);
	exit (-1);
}

void	set_cmd(t_dta *dta, t_cmd *cmd)
{
	int	i;

	i = 0;
	dta->all_path = ft_find_path(dta);
	while (i < dta->pnbr)
	{
		if (ft_get_access(dta, cmd[i].cmd[0]) == NULL)
			error(cmd, dta, "error");
		cmd[i].tpath = ft_get_access(dta, cmd[i].cmd[0]);
		i++;
	}
}

void	first_proc(t_dta *dta, t_cmd *cmd, int pipe_fd[2])
{
	if (dta->pnbr != 1)
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error(cmd, dta, "error");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (execve(cmd->tpath, cmd->lne, dta->newenv) == -1)
		error(cmd, dta, "error");
}

void	middle_proc(t_dta *dta, t_cmd *cmd, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
		error(cmd, dta, "error");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error(cmd, dta, "error");
	close(pipe_fd[1]);
	if (execve(cmd->tpath, cmd->lne, dta->newenv) == -1)
		error(cmd, dta, "error");
}

void	final_proc(t_dta *dta, t_cmd *cmd, int pipe_fd[2])
{
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
		error(cmd, dta, "error");
	if (execve(cmd->tpath, cmd->lne, dta->newenv) == -1)
		error(cmd, dta, "error");
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
		cmd[(*j)].input_fd = pipe_fd[0];
	}
}

void	pipex(t_dta *dta, t_cmd *cmd)
{
	int	j;
	int	pipe_fd[2];

	j = 0;
	set_cmd(dta, cmd);
	while (j < dta->pnbr)
	{
		if (pipe(pipe_fd) == -1)
			error(cmd, dta, "error");
		cmd[j].pid = fork();
		if (cmd[j].pid == -1)
			error(cmd, dta, "error");
		choose_proc(dta, cmd, pipe_fd, &j);
	}
	error(cmd, dta, "");
}
