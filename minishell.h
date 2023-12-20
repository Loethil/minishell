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
# include <ctype.h> 
# include "libft.h"

typedef struct s_dta
{
	char		**tab;
	char		*str;
	char		**all_path;
	char		*true_path;
	char		*line;
	char		*buf; // variable pour <<
	char		**cat_buf; // variable pour cat dans <<
	char		**newenv;
	int			status;
	char		*pwd;
	char		*var; // variable pour les var d'env
	long long	ext; // variable pour exit
	pid_t		pid;
	int			nbr;
	int			lmax;
	int			pnbr; // nombre de pipes
	int			len;
	int			res;
	int			ext_val; // variable pour $?
}				t_dta;

typedef struct s_cmd
{
	char	**lne; //ligne entiere
	char	**cmd; //stock la cmd
	char	**arg; //stock les arguments de la commande
	char	**rdr; //stock les arg de la redirection
	char	*tpath; //pass pour execve
	pid_t	pid; // un pid pour chque case dans le tableau de struct cmd
	int		pfd; //pipe
	int		in_fd;
	int		out_fd;
}				t_cmd;

// UTILS //
void		ft_error(t_cmd *cmd, t_dta *dta, char *err);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_copystring(char *env);
char		*ft_strcpy(char *dst, const char *src);
long long	ft_atoll(char *str);
int			ft_tablen(char **tab);
int			ft_explen(char **tab);
int			ft_invalid(char i);
char		**ft_swap(char **env, int i);
int			ft_whitespace(char *line);

// PWD OR ENV //

int			ft_findpwd(char **env);
int			ft_pwdorenv(t_dta *dta, char **newenv, char *tab);
void		ft_changedir(t_dta *dta, char *path);
char		**ft_find_path(t_dta *dta);
char		*ft_get_access(t_dta *dta, char *argv);
char		**changeenv(t_dta *dta, char **env);
void		ft_dot_cd(t_dta *dta, char *path, int i);
void		ft_chdir_err(char *path);
void		ft_sub_cd(t_dta *dta, char *path, int i);

// EXPORT //

void		ft_export(t_dta *dta, t_cmd *cmd);
int			ft_sub_export(t_dta *dta, t_cmd *cmd, int i, int k);
int			ft_export_input(char *linesplit);
void		ft_export_malloc(t_dta *dta, t_cmd *cmd, int i, int k);
void		ft_export_no_args(t_dta *dta);
char		**ft_sort_env(char **env);

// UNSET //

int			ft_unset(t_dta *dta, t_cmd *cmd);
char		**ft_newenv(t_dta *dta, t_cmd *cmd, int i, int j);
int			ft_unset_input(char *linesplit);
char		*ft_linecpy(char *src);

// EXIT //

void		ft_exit(t_dta *dta, t_cmd *cmd);

// REDIRS //

int			ft_redir(t_dta *dta, t_cmd *cmd);
int			ft_redirect(t_dta *dta, t_cmd *cmd);

// ECHO //

void		ft_echo(t_dta *dta, t_cmd *cmd, int i);
void		ft_print_echo(char **arg, t_dta *dta, int i);
void		ft_var_alloc(t_dta *dta, char *cmd, int i);
int			ft_var_hdl(char *arg);
void		ft_print_var(t_dta *dta, int *k);
char		*ft_var(char *arg, t_dta *dta, int *j);
void		ft_var_master(char **arg, t_dta *dta, int i);
void		ft_print_sq_echo(char **arg, int i);

// SIGNAL //

void		ft_sigint_hdl(int signo);
void		ft_sigquit_hdl(int signo);

// PARS //

void		ft_set_up(t_dta *dta, char *line);
void		ft_pars(t_cmd *cmd, char **tab);
void		ft_cmd_init(t_dta *dta, t_cmd *cmd, char **tab);
int			ft_cmd_simple(t_dta *dta, t_cmd *cmd);
void		ft_pipes(t_dta *dta, int *i);
void		ft_cpy_quotes(t_dta *dta, char *line, int *i);
int			ft_countword(t_dta *dta, char *str);
void		ft_word(t_dta *dta, char *line, int *i, int *j);
char		*ft_getstr(t_dta *dta, char *line, int *i);
void		ft_create_tab(t_dta *dta, char *line);
char		*replace_var(t_dta *dta, char *line, int *i);
char		*ft_freestrjoin(char *s1, char *s2);

// CHECK PARS

void		ft_chevron(t_dta *dta, char *line, int *i);
int			ft_check_quotes(t_dta *dta, char *str, int *i);
int			ft_check_line(t_dta *dta, char *line);
int			ft_check_builtin(char *cmd);
int			ft_check_chevron(char *str);

// PIPE//

int			ft_set_cmd(t_dta *dta, t_cmd *cmd);
void		ft_pipex(t_dta *dta, t_cmd *cmd);

// MAIN //

void		ft_prompt(t_dta *dta);
int			ft_whoitis(t_dta *dta, t_cmd *cmd);

// FREE //

void		ft_destroy(t_dta *dta);
void		ft_free_tab(char **tab);
void		ft_free_cmd(t_dta *dta, t_cmd *cmd);

#endif
