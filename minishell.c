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

/*faire une fonction qui decoupe la ligne et qui range dans les bonnes varaibles
exemple : cmd 1 c'est le premier argument
redir si il y a un '>' etc*/

t_sig	g_sig;

void	ft_exit(t_dta *dta, char *nbr)
{
	char	*verifnbr;

	printf ("exit\n");
	if (nbr[1] == NULL)
		exit (0);
	dta->max = ft_atoll(nbr[2]);
	verifnbr = ft_itoa(dta->max);
	if (strcmp(nbr[1], verifnbr) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", nbr[1]);
		exit (2);
	}
	dta->max %= 256;
	if (nbr[2])
	{
		printf("minishell: exit: too many arguments\n");
		return ;	
	}
	exit(dta->max);
}

void	ft_findcmd(t_dta *dta)
{
	dta->pid = fork();
	if (dta->pid == 0)
	{
		dta->all_path = ft_find_path(dta);
		dta->true_path = ft_get_access(dta, dta->linesplit[0]);
		if (execve(dta->true_path,  &dta->linesplit[0], dta->newenv) == -1)
			printf("error execve\n");
	}
	else
		waitpid(dta->pid, &dta->status, 0);
}

void	ft_whoitis(t_dta *dta)
{
	if (ft_strcmp(dta->linesplit[0], "echo") == 0)
			ft_echo(dta, 1);
	else if (ft_strcmp(dta->linesplit[0], "cd") == 0)
			ft_changedir(dta, dta->linesplit[1]);
	else if (ft_strcmp(dta->linesplit[0], "pwd") == 0)
			ft_pwdorenv(dta->newenv, "PWD");
	else if (ft_strcmp(dta->linesplit[0], "export") == 0)
			ft_export(dta);
	else if (ft_strcmp(dta->linesplit[0], "unset") == 0)
			ft_unset(dta);
	else if (ft_strcmp(dta->linesplit[0], "env") == 0)
			ft_pwdorenv(dta->newenv, "ENV");
	else if (ft_strcmp(dta->linesplit[0], "exit") == 0)
			ft_exit(dta, dta->linesplit[1]);
	else
		ft_findcmd(dta);
}

int	main(int argc, char **argv, char **env)
{
	t_dta	*dta;
	int		i;

	(void)argv;
	dta = malloc(sizeof(t_dta) * 1);
	i = -1;
	if (argc != 1)
		return (0);
	dta->newenv = changeenv(dta, env);
	signal(SIGINT, &ft_sigint_hdl);
	signal(SIGQUIT, &ft_sigquit_hdl);
	ft_prompt(dta);
	return (0);
}
