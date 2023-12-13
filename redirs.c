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

// void	ft_redir(t_dta *dta, t_cmd *cmd)
// {
// 	int	input_fd;
// 	int	output_fd;

// 	dta->pid = fork();
// 	if (dta->pid == 0)
// 	{
// 		if ((input_fd = open(cmd->rdr[0], O_RDONLY)) != -1)
// 		{
// 			dup2(input_fd, STDIN_FILENO);
// 			close(input_fd);
// 			cmd->rdr[0] = NULL;
// 		}
// 		if ((output_fd = open(cmd->rdr[0], O_WRONLY | O_CREAT | O_TRUNC, 0644)))
// 		{
// 			dup2(output_fd, STDOUT_FILENO);
// 			close(output_fd);
// 			cmd->rdr[0] = NULL;
// 		}
// 	}
// 	else
// 		waitpid(dta->pid, NULL, 0);
// }
