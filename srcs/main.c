/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/04 12:38:04 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*ft_initialize_readline(t_env *envcpy)
{
	struct termios	tp;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	if (tcgetattr(0, &tp) == -1)
		printf("Mrd! Terminal!");
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &tp) == -1)
		printf("Mrd! Terminal!");
	rl_bind_key ('\t', rl_insert);
	return (envcpy);
}

int	exec_line(t_node *ast, t_env *env)
{
	int		count;
	pid_t	process;

	if (ast->type == SIMPLECMD && ft_isinn_cmd(*((t_cmd *)ast->node)->args))
		exec_singlebuiltin((t_cmd *)ast->node, env);
	else
	{
		process = fork();
		if (process == -1)
		{
			ft_putstr_fd("minishell: unable to fork", 2);
			return (1);
		}
		else if (!process)
		{
			count = count_exec(ast, 0);
			env->status = exec_simplecmd(ast, count, 1, env);
			printf("exec_line_child-> %i\n", WEXITSTATUS(env->status));
			exit (env->status);
		}
		waitpid(process, &env->status, 0);
		printf("exec_line -> %i\n", WEXITSTATUS(env->status));
	}
	free_ast(ast);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		exit;
	t_node	*ast;
	t_env	*envcpy;

	input = (char *) NULL;
	envcpy = (t_env *)malloc(sizeof(t_env));
	envcpy->next = NULL;
	envcpy->var = malloc(sizeof(char));
	envcpy = ft_make_env(env, envcpy);
	envcpy = ft_initialize_readline(envcpy);
	while (envcpy->exit < 0 && ac && *av)
	{
		input = readline("\033[32;1mMrdShll> \033[0m");
		if (!input)
		{
			printf("\n");
			envcpy->exit = 0;
			break ;
		}
		if (*input)
		{
			add_history(input);
			ast = parse_input(input, envcpy);
			if (!ast)
				ft_putstr_fd("minishell: syntax error\n", 2);
			else
				exec_line(ast, envcpy);
		}
	}
	exit = envcpy->exit;
	ft_end(envcpy);
	return (exit);
}
