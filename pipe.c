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

void	set_pid(t_pip *pip, int nbr)
{
	pip->pid = malloc (nbr * sizeof(pid_t));
	return ;
}

void	proc(t_pip *pip, t_dta *dta, t_cmd *cmd, int *pipe_fd, int num)
{
	close(pipe_fd[0]);
	pip->true_path = ft_get_access(pip->dta, cmd->cmd[num]);
	if (num == dta->pnbr)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			printf("error\n");
		close(pipe_fd[1]);
		if (execve(pip->true_path, &cmd->cmd[num], dta->newenv) == -1)\
			printf("error\n");
	}
	else
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			printf("error\n");
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			printf("error\n");
		close(pipe_fd[1]);
		if (execve(pip->true_path, &cmd->cmd[num], dta->newenv) == -1)
			printf("error\n");
	}
}

void	ft_pipe(t_pip *pip, int *pipe_fd, t_cmd *cmd)
{
	int	status;
	int	nbr;
	int	i;

	nbr = 2;
	i = 0;
	set_pid(pip, nbr);
	pip->true_path = NULL;
	ft_find_path(pip->dta);
	while (i < nbr)
	{
		pip->pid[i] = fork();
		// if (pip->pid[i] == -1)
		// 	error("Error pid\n", pip);
		if (pip->pid[i] == 0)
			proc(pip, pip->dta, cmd, pipe_fd, i);
		else
			waitpid(pip->pid[i], &status, 0);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_dta	*dta;
	t_pip	*pip;
	int		i;

	(void)argv;
	if (pipe(pip->pipe_fd) == -1)
		printf("error\n");
	pip = ft_calloc(1, sizeof(t_pip));
	dta = ft_calloc (1, sizeof(t_dta));
	i = -1;
	if (argc != 1)
		return (0);
	dta->newenv = changeenv(dta, env);
	ft_prompt(dta);
	return (0);
}

