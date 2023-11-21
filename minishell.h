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

typedef	struct s_cmd
{
	char	**tub;
	char	**cmd;
	char	**otn;
	char	**arg;
}				t_cmd;

typedef struct s_data
{
	char	*line;
	char	**all_path;
	char	**splitl;
	char	**newenv;
	char	*true_path;
	int		status;
	char	*pwd;
	long long max;
	int		cnbr;
	pid_t	pid;
}				t_data;


void		ft_exit(t_data *data, char **nbr);
void		ft_findcmd(t_data *data);
void		ft_changedir(t_data *data, char *path);
void		ft_whoitis(t_data *data);
void		ft_pwdorenv(char **newenv, char *tab);
int			ft_strcmp(const char *s1, const char *s2);
long long 	ft_atoll(const char *str);
int			ft_findpwd(char **env);
char		*ft_copystring(char *str);
char		*ft_get_access(t_data *data, char *cmd);
char		**changeenv(t_data *data, char **env);
char		**ft_find_path(t_data *data);
char		**parser(t_data *data, t_cmd *cmd, char *line);
char		*quotes(char *line, char *tab, int *i);
#endif
