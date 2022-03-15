/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/11 09:22:42 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*g_data = NULL;

int	exec_line(t_node *ast, t_env *env)
{
	if (ast->type == SIMPLECMD && ((t_cmd *)ast->node)->args
		&& ft_isinn_cmd(*((t_cmd *)ast->node)->args))
		exec_singlebuiltin((t_cmd *)ast->node, env);
	else
	{
		exec_cmdline(ast, env);
		env->status = WEXITSTATUS(env->status);
	}
	free_ast(ast);
	return (0);
}

t_env	*init_env(char **env)
{
	t_env	*envcpy;

	envcpy = ft_calloc(1, sizeof(t_env));
	if (!envcpy)
		return (NULL);
	if (env && *env)
	{
		envcpy = init_fullenv(env, envcpy);
		if (!envcpy)
			return (NULL);
	}
	else
	{
		envcpy = init_emptyenv(envcpy);
		if (!envcpy)
			return (NULL);
	}
	g_data = malloc(sizeof(t_data));
	if (!g_data)
		return (NULL);
	g_data->env = envcpy;
	return (envcpy);
}

int	onlyspace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && (input[i] < '\t' || input[i] > '\r'))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*envcpy;

	envcpy = init_env(env);
	while (envcpy->exit < 0 && ac && *av)
	{
		input = readline("\033[32;1mMrdShll> \033[0m");
		if (!input)
			envcpy->exit = 0;
		else if (*input && !onlyspace(input))
		{
			add_history(input);
			g_data->ast_init = parse_input(input, envcpy);
			if (!g_data->ast_init)
				ft_putstr_fd("minishell: parse error\n", 2);
			if (!g_data->ast_init)
				g_data->env->status = 1;
			else
				exec_line(g_data->ast_init, envcpy);
		}
		else
			envcpy->status = 0;
	}
	ft_end(envcpy);
	return (0);
}
