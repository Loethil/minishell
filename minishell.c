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

// void	ft_exit(t_data *data, char **nbr)
// {
// 	char	*verifnbr;

// 	printf ("exit\n");
// 	if (nbr[1] == NULL)
// 		exit (0);
// 	data->max = ft_atoll(nbr[2]);
// 	verifnbr = ft_itoa(data->max);
// 	if (strcmp(nbr[1], verifnbr) != 0)
// 	{
// 		printf("minishell: exit: %s: numeric argument required\n", nbr[1]);
// 		exit (2);
// 	}
// 	data->max %= 256;
// 	if (nbr[2])
// 	{
// 		printf("minishell: exit: too many arguments\n");
// 		return ;	
// 	}
// 	exit(data->max);
// }

// void	ft_findcmd(t_data *data)
// {
// 	data->pid = fork();
// 	if (data->pid == 0)
// 	{
// 		data->all_path = ft_find_path(data);
// 		data->true_path = ft_get_access(data, data->linesplit[0]);
// 		if (execve(data->true_path,  &data->linesplit[0], data->newenv) == -1)
// 			printf("error execve\n");
// 	}
// 	else
// 		waitpid(data->pid, &data->status, 0);
// }

// void	ft_changedir(t_data *data, char *path)
// {
// 	int	i;

// 	i = ft_findpwd(data->newenv);
// 	if (path == NULL)
// 	{
// 		data->newenv[i] = "PWD=/home/mbatteux";
// 		chdir("/home/mbatteux");
// 		return ;
// 	}
// 	if (data->linesplit[1][0] == '~')
// 	{
// 		data->newenv[i] = ft_strjoin("PWD=/home/mbatteux/", path + 1);
// 		path = ft_strjoin("/home/mbatteux/", path + 1);
// 		if (chdir(path) == -1)
// 			printf("ERROR CHDIR");
// 		return ;
// 	}
// 	data->true_path = ft_strjoin(data->newenv[i], "/");
// 	data->true_path = ft_strjoin(data->true_path, path);
// 	data->newenv[i] = data->true_path;
// 	data->newenv[i][ft_strlen(data->newenv[i]) - 1] = '\0';
// 	if (chdir(path) == -1)
// 		printf("ERROR CHDIR");
// }

// // une fonction pour ranger les arguements, la commande et les options
// // une fonction qui verifie les commandes

// void	ft_whoitis(t_data *data)
// {
// 	if (ft_strcmp(data->linesplit[0], "echo") == 0)
// 		return ;
// 	if (ft_strcmp(data->linesplit[0], "cd") == 0)
// 		ft_changedir(data, data->linesplit[1]);
// 	else if (ft_strcmp(data->linesplit[0], "pwd") == 0)
// 		ft_pwdorenv(data->newenv, "PWD");
// 	// else if (ft_strcmp(data->linesplit[0], "export") == 0)
// 	// 	ft_echo(data, data->linesplit[1]); // changer le path avec find path apres un export
// 	// else if (ft_strcmp(data->linesplit[0], "unset") == 0)
// 	// 	ft_echo(data, data->linesplit[1]); //
// 	else if (ft_strcmp(data->linesplit[0], "env") == 0)
// 		ft_pwdorenv(data->newenv, "ENV");
// 	else if (ft_strcmp(data->linesplit[0], "exit") == 0)
// 		ft_exit(data, data->linesplit);
// 	else
// 		ft_findcmd(data);
// }

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_cmd	*cmd;
	
	(void)argv;
	if (argc != 1)
		return (0);
	data = malloc (1 * sizeof(t_data));
	cmd = malloc (1 * sizeof(t_cmd));
	data->newenv = changeenv(data, env);
	while (1)
	{
		data->line = readline("minishell:");
		if (data->line[0] == '\0')
			continue ;
		add_history(data->line);
		cmd->tub = parser(data, cmd, data->line);
		printf ("%d\n", data->cnbr);
		// data->linesplit = ft_split(data->line, ' ');
		// parser(data, data->linesplit);
		// ft_whoitis(data);
	}
}
