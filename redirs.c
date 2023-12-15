/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:45:38 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/13 10:45:40 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir(t_dta *dta, t_cmd *cmd)
{
	int	in_fd;
	int	out_fd;

	cmd->in_fd = 0;
	cmd->out_fd = 0;
	if (!cmd->rdr || !cmd->rdr[0])
		return ;
	if (ft_strncmp(cmd->rdr[0], "<", 1) == 0)
	{
		in_fd = open(cmd->rdr[1], O_RDONLY);
		if (in_fd == -1)
			error(cmd, dta, "error");
		cmd->in_fd = in_fd;
	}
	else if (ft_strncmp(cmd->rdr[0], ">", 1) == 0)
	{
		out_fd = open(cmd->rdr[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1)
			error(cmd, dta, "error");
		cmd->out_fd = out_fd;
	}
}
