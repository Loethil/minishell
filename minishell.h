/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:12:44 by mbatteux          #+#    #+#             */
/*   Updated: 2023/11/06 14:12:47 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

typedef struct s_data
{
	char		*line;
	char	**all_path;
	char	**linesplit;
	char	**newenv;
	char	*true_path;
	int		status;
	char	*pwd;
	pid_t	pid;
}				t_data;

typedef	struct s_line
{
	char	**cmd;
	int		cmdnmb;
	char	**arg;
	int		argnmb;
	int		pipenmb;
}				t_line;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_findpwd(char **env);
char	**ft_find_path(t_data *data);
char	*ft_get_access(t_data *data, char *argv);
char	*ft_copystring(char *env);
char	**changeenv(t_data *data, char **env);
#endif
