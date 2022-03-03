/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:48:25 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 22:09:49 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <linux/limits.h>
# include <termios.h>
# include "libft.h"

// token states
# define PIPE			0
# define INREDIR		1
# define OUTREDIR		2
# define LITERAL		3
# define BLANK			4
# define SIMPLEQUOTE	5
# define DOUBLEQUOTE	6

// ast state
# define PIPELINE		7
# define SIMPLECMD		8

// env struct
typedef struct s_env
{
	char			*var;
	struct s_env	*next;
	int				status;
	int				exit;
}					t_env;

// token struct
typedef struct s_tok {
	int		type;
	char	*val;
}	t_tok;

// ast structs
typedef struct s_redir {
	char	*type;
	char	*val;
}	t_redir;

typedef struct s_cmd {
	char	**args;
	t_redir	**redir;
}	t_cmd;

typedef struct s_pipe {
	struct s_node	*left_node;
	struct s_node	*right_node;
}	t_pipe;

typedef struct s_node {
	int		type;
	void	*node;
}	t_node;

//SETUP
//	env.c
char	*get_env_var(char *var, t_env *g_start);
void	ft_add_env(char *var, t_env *envcpy);
void	ft_add_var(char *var, t_env *envcpy);
t_env	*ft_make_env(char **envp, t_env *envcpy);
void	ft_add_var_list(char **var_list, t_env *envcpy);
// setup_utils.c
void	ft_export(char **cmd, t_env *g_start);
void	ft_unset(char **cmd, t_env *g_start);
char	**ft_to_array(t_env *g_start);
void	ft_free_env(t_env *encpy);
void	ft_change_status(char **cmd, t_env *g_start);

// loop_utils.c
void	ft_end(t_env *envcpy);
void	ft_free_array(char **array);
void	ft_add_path(char **cmd, char **path_split);
void	ft_abs_path(char **cmd, t_env *g_start);

//LEXING
//	check.c
int		check_input(char *input);
int		check_toks(t_tok **toks);
//	lexer_utils.c
void	free_toks(t_tok **toks);
int		toktype(char c);
t_tok	**ft_tokalloc(t_tok **toks);
//	lexer.c
t_tok	**ft_lex(char *input);

//EXPANDING
//	expander.c
char	*ft_expandval(char *s, char **env);
int		ft_expand(t_tok **toks, char **env);

//PARSING
//	parser_utils.c
t_tok	**getleft(t_tok **tokens, int index);
t_tok	**getright(t_tok **tokens, int index);
void	free_cmd(t_cmd	*cmd);
void	free_ast(t_node *ast);
t_node	*parse_input(char *input, t_env *env);
//	parser_cmd_utils.c
t_redir	**ft_addredir(t_redir **redir, t_tok **tokens);
char	**ft_addargs(char	**args, t_tok	*tok);
//	parser.c
void	ft_freesplit(char **split);
t_node	*ft_create_ast(t_tok **tokens);
//	heredoc.c
int		ft_heredoc(char *delim, char **env);

//EXECUTION
// inner_utils.c
void	ft_print_echo(char **cmd, int i);
int		exec_singlebuiltin(t_cmd *cmd, t_env *env);
// inner.c
char	*built_in_pwd(void);
void	ft_inn_cd(char *path, t_env *g_start);
void	ft_inn_env(t_env *g_start);
void	ft_inn_exit(char **cmd, t_env *g_start);
void	ft_inn_echo(char **cmd, t_env *g_start);
//	ioctl.c
int	manage_io(int *link, t_redir **redir, int isnotlast, t_env *env);
//	exec_utils.c
void	ft_runinn_cmd(char **cmd, t_env *g_start);
bool	ft_isinn_cmd(char *cmd);
void	ft_run(char	**cmd, t_env *envcpy);
//	exec_simplecmd.c
char	**convert_env(t_env *env);
int		exec_simplecmd(t_node *ast, int count, int num, t_env *env);
#endif
