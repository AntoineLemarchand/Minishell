/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/06 16:22:59 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ast->type == SIMPLECMD && ((t_cmd *)ast->node)->args
		&& ft_isinn_cmd(*((t_cmd *)ast->node)->args))
		exec_singlebuiltin((t_cmd *)ast->node, env);
	else
		exec_cmdline(ast, env);
	free_ast(ast);
	env->status = WEXITSTATUS(env->status);
	return (0);
}

t_env	*init_env(char **env)
{
	t_env	*envcpy;

	envcpy = ft_calloc(1, sizeof(t_env));
	envcpy->next = NULL;
	envcpy->var = ft_calloc(1, sizeof(char));
	envcpy->status = 0;
	envcpy = ft_make_env(env, envcpy);
	envcpy = ft_initialize_readline(envcpy);
	return (envcpy);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_node	*ast;
	t_env	*envcpy;

	envcpy = init_env(env);
	while (envcpy->exit < 0 && ac && *av)
	{
		input = readline("\033[32;1mMrdShll> \033[0m");
		if (!input)
		{
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
	ft_end(envcpy);
	return (0);
}
