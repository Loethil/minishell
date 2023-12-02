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

void	ft_exit(t_data *data, char *nbr)
{
	if (nbr == NULL)
	{
		printf("exit\n");
		exit (0);
	}
	data->max = ft_atoll(nbr);
	data->max %= 256;
	printf("exit\n");
	exit(data->max);
}

void	ft_findcmd(t_data *data)
{
	data->pid = fork();
	if (data->pid == 0)
	{
		data->all_path = ft_find_path(data);
		data->true_path = ft_get_access(data, data->linesplit[0]);
		if (execve(data->true_path,  &data->linesplit[0], data->newenv) == -1)
			printf("error execve\n");
	}
	else
		waitpid(data->pid, &data->status, 0);
}

void	ft_whoitis(t_data *data)
{
	if (ft_strcmp(data->linesplit[0], "echo") == 0)
			ft_echo(data, 1);
	else if (ft_strcmp(data->linesplit[0], "cd") == 0)
			ft_changedir(data, data->linesplit[1]);
	else if (ft_strcmp(data->linesplit[0], "pwd") == 0)
			ft_pwdorenv(data->newenv, "PWD");
	else if (ft_strcmp(data->linesplit[0], "export") == 0)
			ft_export(data);
	else if (ft_strcmp(data->linesplit[0], "unset") == 0)
			ft_unset(data);
	else if (ft_strcmp(data->linesplit[0], "env") == 0)
			ft_pwdorenv(data->newenv, "ENV");
	else if (ft_strcmp(data->linesplit[0], "exit") == 0)
			ft_exit(data, data->linesplit[1]);
	else
		ft_findcmd(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		i;

	(void)argv;
	data = malloc(sizeof(t_data) * 1);
	i = -1;
	if (argc != 1)
		return (0);
	data->newenv = changeenv(data, env);
	signal(SIGINT, &ft_sigint_hdl);
	signal(SIGQUIT, &ft_sigquit_hdl);
	ft_prompt(data);
	return (0);
}
