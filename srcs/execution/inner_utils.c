/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:13:50 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 21:59:40 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_echo(char **cmd, int i)
{
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
}

int	exec_singlebuiltin(t_cmd *cmd, t_env *env)
{
	int	link[2];

	link[0] = dup(0);
	if (link[0] == -1)
		return (1);
	link[1] = dup(0);
	if (link[0] == -1)
	{
		close(link[0]);
		return (1);
	}
	manage_io(link, cmd->redir, 0, env);
	ft_runinn_cmd(cmd->args, env);
	dup2(link[0], 0);
	dup2(link[1], 1);
	close(link[0]);
	close(link[1]);
	return (0);
}
