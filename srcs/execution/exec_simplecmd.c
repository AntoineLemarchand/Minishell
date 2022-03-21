/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:20:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/21 12:20:20 by alemarch         ###   ########.fr       */
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

char	**convert_env(t_env *env)
{
	int		i;
	int		size;
	char	**ret;
	t_env	*begin;

	begin = env;
	size = 1;
	while (env)
	{
		size++;
		env = env->next;
	}
	ret = ft_calloc(size, sizeof(char *));
	i = 0;
	while (begin)
	{
		ret[i] = begin->var;
		begin = begin->next;
		i++;
	}
	return (ret);
}

int	fork_cmd(t_cmd	*cmd, int isnotlast, t_data	*data)
{
	pid_t	process;
	int		link[2];
	int		status;

	pipe(link);
	process = fork();
	if (process == 0)
	{
		signal(SIGINT, cmdprocess);
		close(link[0]);
		if (manage_io(link, cmd->redir, isnotlast, data) != 2
			&& data->env->status != 130)
			ft_run(cmd->args, data->env);
		else if (data->env->status != 130)
			data->env->status = 2;
		close(1);
		status = data->env->status;
		free_data(data);
		exit(status);
	}
	close(link[1]);
	if (dup2(link[0], 0) == -1)
		return (1);
	close(link[0]);
	return (data->env->status);
}

int	exec_simplecmd(t_node	*ast, t_node *ast_init, int num, t_env *env)
{
	if (env->status == 130)
		env->status = 0;
	if (ast->type == PIPELINE)
	{
		env->status = exec_simplecmd(((t_pipe *)ast->node)->left_node, ast_init,
				num % count_exec(ast_init, 0), env);
		num++;
		env->status = exec_simplecmd(((t_pipe *)ast->node)->right_node,
				ast_init, num % count_exec(ast_init, 0), env);
	}
	else
		env->status = fork_cmd(((t_cmd *)ast->node),
				num % count_exec(ast_init, 0), g_data);
	if (num == count_exec(ast_init, 0))
		while (wait(&env->status) > 0)
			;
	return (env->status);
}

int	exec_cmdline(t_node *ast, t_env *env)
{
	pid_t	process;
	int		status;

	process = fork();
	signal(SIGINT, SIG_IGN);
	if (process == -1)
	{
		ft_putendl_fd("minishell: unable to fork", 2);
		return (1);
	}
	else if (process == 0)
	{
		signal(SIGINT, childprocess);
		env->status = exec_simplecmd(ast, ast, 1, env);
		if (env->status == 130)
			exit(env->status);
		status = env->status;
		free_data(g_data);
		close(0);
		exit(WEXITSTATUS(status));
	}
	waitpid(process, &env->status, 0);
	signal(SIGINT, ft_handler);
	return (0);
}
