/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:04:05 by scarpent          #+#    #+#             */
/*   Updated: 2023/12/02 15:04:08 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_hdl(int signo)
{
	(void)signo;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_sigint = 1;
}

// void	ft_sigquit_hdl(int signo)
// {
// 	(void)signo;
// 	g_sig.sigquit = 1;
// }
