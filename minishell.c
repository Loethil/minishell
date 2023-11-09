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

int	echo(char **lineplit, char **env)
{
	if (execve("/usr/bin/echo", lineplit, env) == -1)
		printf("error");
	return (0);
}

void	findcmd(t_data *data, char **env)
{
	data->pid = fork();
	if (data->pid == 0)
	{
		data->all_path = find_path(data);
		data->true_path = get_access(data, data->linesplit[0]);
		if (execve(data->true_path,  &data->linesplit[0], env) == -1)
			printf("error execve\n");
	}
	else
		waitpid(data->pid, &data->status, 0);
}



void	printpwd(t_data *data)
{
	data->pwd = getenv("PWD");
	printf("%s\n", data->pwd);
}

void	printenv(char **env)
{
	int	i;

	i = 0;
	while(env[i])
		printf("%s\n", env[i++]);
}

void	changedir(t_data *data)
{
	(void)data;
	chdir("libft/");
	printf("%s\n", getenv("PWD"));
	//PROBLEME CELA NE CHANGE PAS L'ENV !!!!
}

void	whoitis(t_data *data, char **env)
{
	if (ft_strcmp(data->linesplit[0], "echo") == 0)
			echo(data->linesplit, env); // 
	else if (ft_strcmp(data->linesplit[0], "cd") == 0)
			changedir(data); // 
	else if (ft_strcmp(data->linesplit[0], "pwd") == 0)
			printpwd(data);
	else if (ft_strcmp(data->linesplit[0], "export") == 0)
			echo(data->linesplit, env); //
	else if (ft_strcmp(data->linesplit[0], "unset") == 0)
			echo(data->linesplit, env); //
	else if (ft_strcmp(data->linesplit[0], "env") == 0)
			printenv(env);
	else if (ft_strcmp(data->linesplit[0], "exit") == 0)
			exit(0);
	else
		findcmd(data, env);
}


int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	
	(void)argc;
	(void)argv;
	i = 0;
	while (1)
	{
		data.line = readline("minishell:");
		if (data.line[0] == '\0')
			continue ;
		add_history(data.line);
		data.linesplit = ft_split(data.line, ' ');
		printf("-%s\n", data.line);
		while (data.linesplit[i])
			printf("--%s\n", data.linesplit[i++]);
		whoitis(&data, env);
	}
}
