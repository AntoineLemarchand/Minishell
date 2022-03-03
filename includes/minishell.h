/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:48:25 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 14:51:51 by alemarch         ###   ########.fr       */
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

// global var
extern t_env	*g_start;

//SETUP
//	env.c
char	*get_env_var(char *var);
void	ft_add_env(char *var);
void	ft_add_var(char *var);
void	ft_make_env(char **envp);
void	ft_add_var_list(char **var_list);
// setup_utils.c
void	ft_export(char **cmd);
void	ft_unset(char **cmd);
char	**ft_to_array(void);
void	ft_free_env(void);
void	ft_change_status(char **cmd);

// loop_utils.c
void	ft_end(void);
void	ft_free_array(char **array);
void	ft_add_path(char **cmd, char **path_split);
void	ft_abs_path(char **cmd);

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
t_node	*parse_input(char *input, char **env);
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
// inner.c
char	*built_in_pwd(void);
void	ft_inn_cd(char *path);
void	ft_inn_env(void);
void	ft_inn_exit(char **cmd);
void	ft_inn_echo(char **cmd);
//	ioctl.c
int	manage_io(int *link, t_redir **redir, int isnotlast, char **env);
//	exec_utils.c
void	ft_run(char **cmd);
//	exec_simplecmd.c
int		exec_simplecmd(t_node *ast, int count, int num, char **env);
#endif
