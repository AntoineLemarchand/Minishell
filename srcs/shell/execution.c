/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:01:57 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/16 23:05:39 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	list_pipe(t_pip *pipcell, t_copy *cmdarg, int *fdd)
{
	t_pip	*tmp;

	while (pipcell)
	{
		tmp = pipcell;
		if (parsing(pipcell->cmd_pip, cmdarg) == NULL)
		{
			if (tmp->cmd_pip)
				free(tmp->cmd_pip);
			free(tmp);
			free_cmdarg(cmdarg);
			break ;
		}
		*fdd = run_pipe(pipcell, cmdarg, *fdd);
		pipcell = pipcell->next;
		free_cmdarg(cmdarg);
	}
	close(*fdd);
}

static void	clean_redir(t_copy *copy, int savein, int saveout1, int saveout2)
{
	if (copy->redir.in)
		dup2(savein, 0);
	if (copy->redir.out1)
		dup2(saveout1, 1);
	if (copy->redir.out2)
		dup2(saveout2, 2);
}

static void	redir_dup(t_copy *cmdarg)
{
	int		savein;
	int		saveout1;
	int		saveout2;

	savein = 0;
	if (!savein && cmdarg->redir.in != NULL)
	{
		savein = dup(0);
		close(0);
		dup2(cmdarg->redir.sstdin, 0);
	}
	saveout1 = 0;
	if (!saveout1 && cmdarg->redir.out1)
	{
		saveout1 = dup(1);
		close(1);
		dup2(cmdarg->redir.sstdout, 1);
	}
	saveout2 = 0;
	if (!saveout2 && cmdarg->redir.out2)
	{
		saveout2 = dup(2);
		close(2);
		dup2(cmdarg->redir.sstderr, 2);
	}
	exec(cmdarg->args, 0, cmdarg);
	clean_redir(cmdarg, savein, saveout1, saveout2);
}

void	minishell(t_sep *list, t_copy *cmdarg)
{
	int		fdd;
	int		i;

	fdd = dup(0);
	i = 0;
	while (list)
	{
		if (list->pipcell != NULL)
			list_pipe(list->pipcell, cmdarg, &fdd);
		else
		{
			if (parsing(list->cmd_sep, cmdarg) == NULL)
			{
				free_cmdarg(cmdarg);
				break ;
			}
			execution(cmdarg, 0);
			free_cmdarg(cmdarg);
		}
		list = list->next;
		i++;
	}
}

void	execution(t_copy *cmdarg, int pipe)
{
	if (cmdarg->redir.in || cmdarg->redir.out1 || cmdarg->redir.out2)
		redir_dup(cmdarg);
	else
		exec(cmdarg->args, pipe, cmdarg);
}
