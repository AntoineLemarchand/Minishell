/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioctl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:26:21 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 14:15:52 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_ioerror(char *file, int isinput)
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

static void	clean_io(int *fds, int *link, t_redir *redir)
{
	if (fds[1] != link[1] && (!strncmp(redir->type, ">\0", 2)
			|| !strncmp(redir->type, ">>\0", 3)))
		close(fds[1]);
	else if (fds[0] != 0 && (!strncmp(redir->type, "<\0", 2)
			|| !strncmp(redir->type, "<<\0", 3)))
		close(fds[0]);
}

static void	io_helper(t_redir *redir, int *fds)
{
	if (!strncmp(redir->type, ">\0", 2))
		fds[1] = open(redir->val, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (!strncmp(redir->type, ">>\0", 3))
		fds[1] = open(redir->val, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (!strncmp(redir->type, "<\0", 2))
		fds[0] = open(redir->val, O_RDONLY);
	else
		fds[0] = ft_heredoc(redir->val);
}

int	manage_io(int *link, t_redir **redir, int num, int count)
{
	int	i;
	int	fds[2];

	i = 0;
	fds[1] = link[1];
	fds[0] = 0;
	while (redir && redir[i])
	{
		clean_io(fds, link, redir[i]);
		io_helper(redir[i], fds);
		if (fds[0] == -1)
			return (ft_ioerror(redir[i]->val, 1));
		else if (fds[1] == -1)
			return (ft_ioerror(redir[i]->val, 0));
		i++;
	}
	if (dup2(fds[0], 0) == -1)
		return (1);
	if ((fds[1] != link[1] || num < count) && dup2(fds[1], 1) == -1)
		return (1);
	return (0);
}
