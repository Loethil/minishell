/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:43:46 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/21 15:43:49 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sub_redir(t_dta *dta, t_cmd *cmd, int i)
{
	if (!cmd->rdr[i])
	{
		printf("missing rdr\n");
		return (1);
	}
	cmd->out_fd = open(cmd->rdr[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out_fd == -1)
		ft_error(cmd, dta, cmd->cmd[0]);
	if (dup2(cmd->out_fd, STDOUT_FILENO) == -1)
		ft_error(cmd, dta, cmd->cmd[0]);
	return (0);
}

int	ft_read_redir(t_dta *dta, t_cmd *cmd, int i)
{
	if (!cmd->rdr[i])
	{
		printf("missing rdr\n");
		return (1);
	}
	cmd->in_fd = open(cmd->rdr[i], O_RDONLY);
	if (cmd->in_fd == -1)
		ft_error(cmd, dta, cmd->cmd[0]);
	if (dup2(cmd->in_fd, STDIN_FILENO) == -1)
		ft_error(cmd, dta, cmd->cmd[0]);
	return (0);
}

int	ft_app_redir(t_dta *dta, t_cmd *cmd, int i)
{
	if (!cmd->rdr[i])
	{
		printf("missing rdr\n");
		return (1);
	}
	cmd->out_fd = open(cmd->rdr[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out_fd == -1)
		ft_error(cmd, dta, cmd->cmd[0]);
	if (dup2(cmd->out_fd, STDOUT_FILENO) == -1)
		ft_error(cmd, dta, cmd->cmd[0]);
	return (0);
}
