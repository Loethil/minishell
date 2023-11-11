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

/*recoder echo avec l'option -n, ou faire les bonus de pipex (gerer plusieurs pipe)*/
/*faire une fonction qui decoupe la ligne et qui range dans les bonnes varaibles
exemple : cmd 1 c'est le premier argument
redir si il y a un '>' etc*/

int	ft_echo(t_data *data, char *linesplit)
{
	if (execve("/usr/bin/echo", &linesplit, data->newenv) == -1)
		printf("error");
	return (0);
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

void	ft_printpwd(t_data *data)
{
	int	i;

	i = ft_findpwd(data->newenv);
	printf("%s\n", data->newenv[i] + 4);
}

void	ft_printenv(t_data *data)
{
	int	i;

	i = 0;
	while(data->newenv[i])
		printf("%s\n", data->newenv[i++]);
}

void	ft_changedir(t_data *data)
{
	int	i;

	i = ft_findpwd(data->newenv);
	// data->true_path = ft_strjoin(data->true_path, "/");
	data->true_path = ft_strjoin(data->newenv[i], "/");
	data->true_path = ft_strjoin(data->true_path, data->linesplit[1]);
	data->newenv[i] = data->true_path;
	printf("%s\n", data->true_path);
	chdir(data->linesplit[1]);
	//path relatif marche mais pas path absolu
}

void	ft_whoitis(t_data *data)
{
	if (ft_strcmp(data->linesplit[0], "echo") == 0)
			ft_echo(data, data->linesplit[1]); // 
	else if (ft_strcmp(data->linesplit[0], "cd") == 0)
			ft_changedir(data);
	else if (ft_strcmp(data->linesplit[0], "pwd") == 0)
			ft_printpwd(data);
	else if (ft_strcmp(data->linesplit[0], "export") == 0)
			ft_echo(data, data->linesplit[1]); //
	else if (ft_strcmp(data->linesplit[0], "unset") == 0)
			ft_echo(data, data->linesplit[1]); //
	else if (ft_strcmp(data->linesplit[0], "env") == 0)
			ft_printenv(data);
	else if (ft_strcmp(data->linesplit[0], "exit") == 0)
			exit(0);
	else
		ft_findcmd(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	
	(void)argv;
	i = 0;
	if (argc != 1)
		return (0);
	data.newenv = changeenv(&data, env);
	while (1)
	{
		data.line = readline("minishell:");
		if (data.line[0] == '\0')
			continue ;
		add_history(data.line);
		data.linesplit = ft_split(data.line, ' ');
		// printf("-%s\n", data.line);
		// while (data.linesplit[i])
		// 	printf("--%s\n", data.linesplit[i++]);
		ft_whoitis(&data);
	}
}
