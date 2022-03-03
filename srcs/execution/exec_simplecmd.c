/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:20:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 16:30:39 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_cmd(t_cmd	*cmd, int num, int count, char **env)
{
	pid_t	process;
	int		link[2];

	pipe(link);
	process = fork();
	if (process == 0)
	{
		close(link[0]);
		manage_io(link, cmd->redir, num % count, env);
		close(link[1]);
		ft_run(cmd->args);
		exit(127);
	}
	close(link[1]);
	if (dup2(link[0], 0) == -1)
		return (1);
	close(link[0]);
	waitpid(process, NULL, 0);
	return (0);
}

int	exec_simplecmd(t_node	*ast, int count, int num, char **env)
{
	if (ast->type == PIPELINE)
	{
		if (exec_simplecmd(((t_pipe *)ast->node)->left_node, count, num++, env))
			return (1);
		if (exec_simplecmd(((t_pipe *)ast->node)->right_node, count, num, env))
			return (1);
	}
	else
	{
		if (fork_cmd(((t_cmd *)ast->node), num, count, env))
			return (1);
	}
	return (0);
}
