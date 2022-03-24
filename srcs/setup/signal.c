/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:19:48 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/24 14:39:39 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int status)
{
	if (status == 2)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_data->env->status = 130;
	}
	else
		return ;
}

int	manage_errno(int err)
{
	if (err == 2)
	{
		ft_putendl_fd("", 2);
		return (err + 128);
	}
	else if (err == 131)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		return (err);
	}
	return (WEXITSTATUS(err));
}

void	cmdprocess(int i)
{
	free_data(g_data);
	if (i == 2)
		exit(130);
	else
		exit(131);
}

void	heredoc_process(int i)
{
	(void)i;
	if (i == 2)
		write(2, "\n", 1);
	free_ast(g_data->ast_init);
	ft_free_env(g_data->env);
	free(g_data);
	exit(130);
}

void	none(int i)
{
	(void)i;
	printf("\n");
}
