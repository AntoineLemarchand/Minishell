/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:20:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/24 10:14:25 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmd	*cmd, int fdin, int fdout)
{
	(void)cmd;
	(void)fdin;
	(void)fdout;
	return (0);
}

int	exec_simplecmd(t_node	*ast, int fdin, int fdout)
{
	if (ast->type == PIPELINE)
	{
		if (exec_simplecmd(((t_pipe *)ast->node)->left_node, fdin, fdout)
			|| exec_simplecmd(((t_pipe *)ast->node)->right_node, fdin, fdout))
			return (1);
	}
	else
		if (exec_cmd(((t_cmd *)ast->node), fdin, fdout))
			return (1);
	return (0);
}
