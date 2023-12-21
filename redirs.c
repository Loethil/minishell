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

void	ft_tmp_buf(t_dta *dta, t_cmd *cmd)
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
			return ;
		}
		// if (g_sigint == 1)
		// {
		// 	g_sigint = 0;
		// 	dta->ext_val = 130;
		// 	return ;
		// }
		if (dta->line[0] == '\0' || ft_whitespace(dta->line))
			continue ;
		if (ft_strncmp(dta->buf, cmd->rdr[1], ft_strlen(cmd->rdr[1])) == 0)
		{
			if (ft_strncmp(cmd->cmd[0], "cat", 3) == 0)
			{
				while (dta->cat_buf[++i])
					printf("%s\n", dta->cat_buf[i]);
			}
			return ;
		}
		if (ft_strncmp(cmd->cmd[0], "cat", 3) == 0)
			ft_buf_cpy(dta);
	}
}

int	ft_sub_redir(t_dta *dta, t_cmd *cmd, int i)
{
	if (!cmd->rdr[i])
	{
		printf("missing rdr\n");
		return (1);
	}
	cmd->out_fd = open(cmd->rdr[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out_fd == -1)
		ft_error(cmd, dta, "error");
	if (dup2(cmd->out_fd, STDOUT_FILENO) == -1)
		ft_error(cmd, dta, "error");
	return (0);
}

int ft_read_redir(t_dta *dta, t_cmd *cmd, int i)
{
	if (!cmd->rdr[i])
	{
		printf("missing rdr\n");
		return (1);
	}
	cmd->in_fd = open(cmd->rdr[i], O_RDONLY);
	if (cmd->in_fd == -1)
		ft_error(cmd, dta, "error");
	if (dup2(cmd->in_fd, STDIN_FILENO) == -1)
		ft_error(cmd, dta, "error");
	return (0);
}

int	ft_app_redir(t_dta *dta, t_cmd *cmd, int i)
{
	if (!cmd->rdr[i])
	{
		printf("missing rdr\n");
		return (1);
	}
	cmd->out_fd = open(cmd->rdr[i],	O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out_fd == -1)
		ft_error(cmd, dta, "error");
	if (dup2(cmd->out_fd, STDOUT_FILENO) == -1)
		ft_error(cmd, dta, "error");
	return (0);
}

int	ft_redirect(t_dta *dta, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	if (!cmd->rdr || !cmd->rdr[0])
		return (-1);
	while (i < ft_tablen(cmd->rdr) && cmd->rdr[i])
	{
		if (ft_strncmp(cmd->rdr[i], "<<", 2) == 0)
		{
			ft_tmp_buf(dta, cmd); // non fini
			return (1);
		}
		else if (ft_strncmp(cmd->rdr[i], ">>", 2) == 0)
		{
			if (ft_app_redir(dta, cmd, ++i))
				return (1);
		}
		else if (ft_strncmp(cmd->rdr[i], "<", 1) == 0)
		{
			if(ft_read_redir(dta, cmd, i))
				return (1);
		}
		else if (ft_strncmp(cmd->rdr[i], ">", 1) == 0)
			if (ft_sub_redir(dta, cmd, ++i))
				return (1);
		i++;
	}
	return (0);
}
