/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:20:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 11:09:35 by alemarch         ###   ########.fr       */
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

int	manage_io(int *link, t_redir **redir, int num, int count)
{
	int	i;
	int	fds[2];

	i = 0;
	fds[1] = link[1];
	while (redir && redir[i])
	{
		if (!strncmp(redir[i]->type, ">\0", 2))
			fds[1] = open(redir[i]->val, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (!strncmp(redir[i]->type, ">>\0", 3))
			fds[1] = open(redir[i]->val, O_CREAT | O_APPEND | O_WRONLY, 0644);
		i++;
	}
	if (fds[1] != link[1] || num < count)
		dup2(fds[1], 1);
	return (0);
}

int	fork_cmd(t_cmd	*cmd, int num, int count)
{
	pid_t	process;
	int		link[2];

	pipe(link);
	process = fork();
	if (process == 0)
	{
		close(link[0]);
		manage_io(link, cmd->redir, num, count);
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

int	exec_simplecmd(t_node	*ast, int count, int num)
{
	if (ast->type == PIPELINE)
	{
		if (exec_simplecmd(((t_pipe *)ast->node)->left_node, count, num++))
			return (1);
		if (exec_simplecmd(((t_pipe *)ast->node)->right_node, count, num))
			return (1);
	}
	else
	{
		if (fork_cmd(((t_cmd *)ast->node), num, count))
			return (1);
	}
	return (0);
}
