/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:54:54 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/17 10:05:28 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include "../libft/libft.h"

char					**g_envs;
pid_t					g_pid;
int						g_error;
int						g_status;
int						g_tester;

typedef struct s_sep
{
	char				*cmd_sep;
	struct s_sep		*prev;
	struct s_sep		*next;
	struct s_pip		*pipcell;
}						t_sep;

typedef struct s_pip
{
	char				*cmd_pip;
	struct s_pip		*prev;
	struct s_pip		*next;
}						t_pip;

typedef struct s_redir
{
	char				*out1;
	char				*out2;
	char				*in;
	int					sstdout;
	int					sstderr;
	int					sstdin;
	int					end;
	int					i;
	char				*name;
	char				*value;
}						t_redir;

typedef struct s_copy
{
	t_sep				*list;
	char				**cmdssep;
	char				*wc;
	char				**args;
	char				*cmd;
	int					i;
	int					j;
	t_redir				redir;
	char				**tmp;
	char				*arg;
}						t_copy;

void					loop(void);
void					loop_tester(char *line);

t_sep					*parse_sep(void);
void					print_list(t_sep *list);
t_sep					*add_cell(t_sep *list, char *cmd_sep, int pos);

void					parse_pip(t_sep *list);
void					print_pip_list(t_pip *piplist);
int						run_pipe(t_pip *pipcell, t_copy *cmdargs, int fdd);
void					status_child(void);

int						redirection(t_copy *copy, int i);
int						redir_quoting(t_copy *copy, int i, char *file);
int						redir_out(t_copy *copy, int i);
int						redir_out_error(t_copy *copy, int i);
int						create_file(t_copy *copy, int type);
void					redir_in_util(t_copy *copy, int i);

char					*parsing(char *whole_cmd, t_copy *copy);
int						options(t_copy *copy, size_t i, size_t	j);
char					*args(t_copy *copy, size_t i, int j);

int						quote_error(char c);
int						d_quote(t_copy *copy, int j);
int						s_quote(t_copy *copy);
int						d_quote_arg(t_copy *copy, size_t i, int j);
int						s_quote_arg(t_copy *copy, size_t i);
int						s_quote_redir(t_copy *copy, char *str);
int						d_quote_redir(t_copy *copy, char *str, int std);
int						inside_quote(char *str, int i);

void					minishell(t_sep *list, t_copy *cmdarg);
void					execution(t_copy *cmdarg, int pipe);
void					prompt(void);
int						exec(char **args, int pipe, t_copy *copy);
int						check_builtin(char **args, t_copy *copy);
int						check_bins(char **args, int pipe);
int						has_perm(char **args, char *bin, struct stat statbuf,
							int pipe);
int						run(char **args, char *bin, int pipe);
int						return_error(char *cmd, char *msg, int ret, int status);

void					call(t_copy *cmdarg);

char					*get_env(char *env);
int						set_env(char *env, char *new_env);
void					print_envs(void);
char					**get_path(void);
char					**realloc_envs(size_t size);
ssize_t					find_env(char *env);
size_t					get_envs_count(void);
int						env(t_copy *copy, int arg, int i, int space);
int						env_redir(t_copy *copy, int arg, int space);
int						no_value(t_copy *copy, char *value);
int						status_env(t_copy *copy, int arg, int i);
void					env_copy(t_copy *copy, int arg, int i, char *value);
int						init_value_name(t_copy *copy);

int						run_echo(char **args);
int						run_cd(char **args);
int						run_unset(char **args);
int						run_export(char **args);
void					sort_env(void);
int						run_env(void);
int						set_directory(char *path, int home);
void					run_exit(char **args, t_copy *copy);
int						check_export_name(char *args);

void					sigint_handler(int sign_num);

int						error_exit(char *str, char *msg);
int						syntax_error(char *str, char c, int i);
int						error_msg(char *str, int i, char c);
void					error_ambiguous(char *name);
void					ft_exit(t_copy *copy, int i);
int						check_space_colon(char *line);

void					free_cmdarg(t_copy *copy);
void					free_list(t_sep *list);
void					free_list_pip(t_pip *pipcell);

#endif
