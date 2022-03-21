/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:19:48 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/21 14:52:55 by alemarch         ###   ########.fr       */
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

void	childprocess(int i)
{
	(void)i;
	free_data(g_data);
	printf("\n");
	exit(130);
}

void	cmdprocess(int i)
{
	(void)i;
	free_data(g_data);
	if (i == 2)
		exit(130);
	else
	{
		printf("Quit (core dumped)\n");
		exit(131);
	}
}

void	heredoc_process(int i)
{
	(void)i;
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
