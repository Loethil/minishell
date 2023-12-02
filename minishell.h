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
# include <signal.h>
# include "libft.h"

typedef struct s_dta
{
	char		*str;
	char		**all_path;
	char		**lsplit;
	char		**newenv;
	char		*true_path;
	int			status;
	char		*pwd;
	long long 	max;
	pid_t		pid;
	int			nbr;
	int			lmax;
	int			pnbr;
	int			len;
}				t_dta;

typedef	struct s_cmd
{
	char		**cmd; //stock la cmd
	char		**arg; //stock les arguments de la commande
	char		*rdr;  //stock les arg de la redirection
	int			dlr;   // dollar macro
}				t_cmd;

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
}				t_sig;

// UTILS //

int			ft_strcmp(const char *s1, const char *s2);
char		*ft_copystring(char *env);
char		*ft_strcpy(char *dst, const char *src);
long long	ft_atoll(const char *str);
int			ft_tablen(char **tab);
int			ft_invalid(char i);
char		**ft_swap(char **env, int i);
int			ft_whitespace(char *line);

// PWD OR ENV //

int			ft_findpwd(char **env);
void		ft_pwdorenv(char **newenv, char *tab);
void		ft_changedir(t_dta *dta, char *path);
char		**ft_find_path(t_dta *dta);
char		*ft_get_access(t_dta *dta, char *argv);
char		**changeenv(t_dta *dta, char **env);

// EXPORT //

int			ft_export(t_dta *dta);
int			ft_sub_export(t_dta *dta, int i, int k);
int			ft_export_input(char *linesplit);
void		ft_export_malloc(t_dta *dta, int i, int k);
void		ft_export_no_args(t_dta *dta);
char		**ft_sort_env(char **env);
void		ft_export_no_args(t_dta *dta);

// UNSET //

int			ft_unset(t_dta *dta);
char		**ft_newenv(t_dta *dta, int i, int j);
int			ft_unset_input(char *linesplit);
char		*ft_linecpy(char *src);

// EXIT //

void		ft_exit(t_dta *dta, char *nbr);

// ECHO //

int			ft_echo(t_dta *dta, int i);
void		ft_print_echo(char **linesplit, int i);

// SIGNAL //

void		ft_sigint_hdl(int signo);
void		ft_sigquit_hdl(int signo);

// MAIN //

void		ft_prompt(t_dta *dta);
void		ft_whoitis(t_dta *dta);
void		ft_findcmd(t_dta *dta);

extern t_sig g_sig;
#endif
