/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:20:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/02 12:28:58 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ioerror(char *file, int isinput)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" ", 2);
	if (isinput)
	{
		ft_putstr_fd(strerror(2), 2);
		return (2);
	}
	ft_putstr_fd(strerror(1), 2);
	return (1);
}

int	manage_io(int *link, t_redir **redir)
{
	(void)link;
	(void)redir;
	return (0);
}

void	exec_cmd(char **args, char **env)
{
	execve(*args, args, env);
	ft_putstr_fd(*args, 2);
	ft_putstr_fd(": Command not found\n", 2);
}

int	fork_cmd(t_cmd	*cmd, char **env, int num, int count)
{
	pid_t	process;
	int		link[2];

	pipe(link);
	process = fork();
	if (process == 0)
	{
		if (num < count)
		{
			close(link[0]);
			if (dup2(link[1], 1) == -1)
				return (1);
			close(link[1]);
		}
		exec_cmd(cmd->args, env);
		exit(127);
	}
	close(link[1]);
	if (dup2(link[0], 0) == -1)
		return (1);
	close(link[0]);
	waitpid(process, NULL, 0);
	return (0);
}

int	exec_simplecmd(t_node	*ast, char **env, int count, int num)
{
	if (ast->type == PIPELINE)
	{
		if (exec_simplecmd(((t_pipe *)ast->node)->left_node, env, count, num++))
			return (1);
		if (exec_simplecmd(((t_pipe *)ast->node)->right_node, env, count, num))
			return (1);
	}
	else
	{
		if (fork_cmd(((t_cmd *)ast->node), env, num, count))
			return (1);
	}
	return (0);
}
