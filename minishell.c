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

t_sig sig;

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

void	ft_pwdorenv(char **newenv, char *tab)
{
	int	i;

	if (strcmp(tab, "PWD") == 0)
	{
		i = ft_findpwd(newenv);
		printf("%s\n", newenv[i] + 4);
	}
	if (strcmp(tab, "ENV") == 0)
	{
		i = 0;
		while(newenv[i])
			printf("%s\n", newenv[i++]);
	}
}

void	ft_changedir(t_data *data, char *path)
{
	int	i;

	i = ft_findpwd(data->newenv);
	if (data->linesplit[1][0] == '~')
	{
		data->newenv[i] = ft_strjoin("PWD=/home/mbatteux", path + 1);
		path = ft_strjoin("/home/mbatteux/", path + 1);
		if (chdir(path) == -1)
			printf("ERROR CHDIR\n");
		return ;
	}
	data->true_path = ft_strjoin(data->newenv[i], "/");
	data->true_path = ft_strjoin(data->true_path, path);
	data->newenv[i] = data->true_path;
	if (chdir(path) == -1)
		printf("ERROR CHDIR\n");
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

void	sigint_hdl(int signo)
{
	(void)signo;
	printf("\nminishell: ");
	sig.sigint = 1;
}

void	sigquit_hdl(int signo)
{
	(void)signo;
	sig.sigquit = 1;
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
	signal(SIGINT, &sigint_hdl);
	signal(SIGQUIT, &sigquit_hdl);
	ft_prompt(data);
	return (0);
}
