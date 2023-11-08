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

int	echo(char **tabsplit, char **env)
{
	// (void)env;
	if (execve("/usr/bin/echo", tabsplit, env) == -1)
		printf("error");
	// printf("%s\n", tabsplit[1]);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char *tab;
	char	**tabsplit;
	int 	status;
	t_data	data;
	int	i = 0;


	(void)argc;
	(void)argv;
	while (1)
	{
		tab = readline("minishell:");
		if (tab[0] == '\0')
			continue ;
		add_history(tab);
		tabsplit = ft_split(tab, ' ');
		printf("-%s\n", tab);
		while (tabsplit[i])
			printf("--%s\n", tabsplit[i++]);
		data.pid = fork();
		if (data.pid == 0)
		{
			if (ft_strncmp(tabsplit[0], "echo", 4) == 0)
				echo(tabsplit, env);
		}
		else
			waitpid(data.pid, &status, 0);
	}
}
