/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/02 15:15:01 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_start;

char	*readline(const char *prompt);

static int	count_exec(t_node *ast, int count)
{
	if (ast->type == PIPELINE)
	{
		count += count_exec(((t_pipe *)ast->node)->left_node, 0);
		count += count_exec(((t_pipe *)ast->node)->right_node, 0);
	}
	else
		count++;
	return (count);
}

void	ft_handler(int status)
{
	if (status == 2)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else
		return ;
}

void	ft_initialize_readline(void)
{
	struct termios	tp;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	if (tcgetattr(0, &tp) == -1)
		ft_putstr_fd("minishell: could not load term", 2);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &tp) == -1)
		ft_putstr_fd("minishell: could not load term", 2);
	g_start->exit = -1;
	g_start->status = 0;
	rl_bind_key ('\t', rl_insert);
}

t_node	*parse_input(char *input, char **env)
{
	t_tok	**tokens;
	t_node	*ret;

	tokens = ft_lex(input);
	if (!tokens)
		return (NULL);
	if (ft_expand(tokens, env))
	{
		free_toks(tokens);
		return (NULL);
	}
	ret = ft_create_ast(tokens);
	free_toks(tokens);
	if (!ret)
		return (NULL);
	return (ret);
}

int	exec_line(t_node *ast, char **env)
{
	int		count;
	pid_t	process;

	process = fork();
	if (process == -1)
	{
		ft_putstr_fd("minishell: unable to fork", 2);
		return (1);
	}
	else if (!process)
	{
		count = count_exec(ast, 0);
		exec_simplecmd(ast, env, count, 1);
		exit (0);
	}
	waitpid(process, NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		exit;
	t_node	*ast;

	(void)ac;
	input = (char *) NULL;
	ft_make_env(env);
	ft_initialize_readline();
	while (g_start->exit < 0)
	{
		input = readline("\033[32;1mMrdShll> \033[0m");
		if (input && *input)
			add_history(input);
		else
		{
			printf("\n");
			g_start->exit = 0;
			break ;
		}
		ast = parse_input(input, env);
		if (!ast)
			printf("%s: \"%s\": syntax error\n", av[0], input);
		else
		{
			exec_line(ast, env);
			free_ast(ast);
		}
		input = (char *) NULL;
	}
	exit = g_start->exit;
	ft_end();
	return (exit);
}
