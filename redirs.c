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

void	ft_buf_cpy(t_dta *dta)
{
	static int	j = 0;

	if (!dta->cat_buf)
		dta->cat_buf = ft_calloc(1000, sizeof(char *));
	dta->cat_buf[j++] = dta->buf;
}

int	ft_tmp_buf(t_dta *dta, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (1)
	{
		dta->buf = readline("> ");
		if (dta->buf == NULL)
		{
			printf("minishell: warning: EOF encountered (wanted: '%s')\n",
				cmd->rdr[1]);
			return (1);
		}
		if (dta->line[0] == '\0' || ft_whitespace(dta->line))
			continue ;
		if (ft_strncmp(dta->buf, cmd->rdr[1], ft_strlen(cmd->rdr[1])) == 0)
		{
			if (ft_strncmp(cmd->cmd[0], "cat", 3) == 0)
			{
				while (dta->cat_buf[++i])
					printf("%s\n", dta->cat_buf[i]);
			}
			return (1);
		}
		if (ft_strncmp(cmd->cmd[0], "cat", 3) == 0)
			ft_buf_cpy(dta);
	}
	return (0);
}

int	ft_redir(t_dta *dta, t_cmd *cmd)
{
	int	in_fd;
	int	out_fd;

	cmd->in_fd = 0;
	cmd->out_fd = 0;
	if (!cmd->rdr || !cmd->rdr[0])
		return (0);
	if (ft_strncmp(cmd->rdr[0], "<<", 2) == 0)
	{
		if (ft_tmp_buf(dta, cmd))
			return (1);
	}
	else if (ft_strncmp(cmd->rdr[0], ">>", 2) == 0)
	{
		out_fd = open(cmd->rdr[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_fd == -1)
			error(cmd, dta, "error");
		cmd->out_fd = out_fd;
	}
	else if (ft_strncmp(cmd->rdr[0], "<", 1) == 0)
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
	return (0);
}
