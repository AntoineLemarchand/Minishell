/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:20:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/05 11:04:51 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	fork_cmd(t_cmd	*cmd, int isnotlast, t_env *env)
{
	pid_t	process;
	int		link[2];

	pipe(link);
	process = fork();
	if (process == 0)
	{
		close(link[0]);
		manage_io(link, cmd->redir, isnotlast, env);
		close(link[1]);
		ft_run(cmd->args, env);
		exit(127);
	}
	close(link[1]);
	if (dup2(link[0], 0) == -1)
		return (1);
	close(link[0]);
	return (env->status);
}

int	exec_simplecmd(t_node	*ast, int count, int num, t_env *env)
{
	if (ast->type == PIPELINE)
	{
		exec_simplecmd(((t_pipe *)ast->node)->left_node,
			count, num++, env);
		env->status = exec_simplecmd(((t_pipe *)ast->node)->right_node,
				count, num, env);
	}
	else
		env->status = fork_cmd(((t_cmd *)ast->node), num % count, env);
	if (num == count)
		while (wait(&env->status) > 0)
			;
	return (env->status);
}

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

int	exec_cmdline(t_node *ast, t_env *env)
{
	int		count;
	pid_t	process;

	process = fork();
	if (process == -1)
	{
		ft_putstr_fd("minishell: unable to fork", 2);
		return (1);
	}
	else if (process == 0)
	{
		signal(SIGINT, childprocess);
		count = count_exec(ast, 0);
		env->status = exec_simplecmd(ast, count, 1, env);
		exit(WEXITSTATUS(env->status));
	}
	signal(SIGINT, none);
	waitpid(process, &env->status, 0);
	signal(SIGINT, ft_handler);
	return (0);
}
