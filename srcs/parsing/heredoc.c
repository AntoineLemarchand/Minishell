/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:09:32 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/03 14:12:51 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	fill_heredoc(char *delim, int fd)
{
	char	*input;
	char	*temp;
	int		end;

	end = 0;
	while (!end)
	{
		temp = readline("\033[32;1m>\033[0m");
		if (!ft_strncmp(temp, delim, ft_strlen(delim)))
			end = 1;
		else
		{
			input = ft_strjoin(temp, "\n");
			if (!input)
				return (1);
			write(fd, input, ft_strlen(input));
			free(input);
		}
		free(temp);
	}
	return (0);
}

int	ft_heredoc(char *delim)
{
	int		fd;

	fd = open("/tmp/tmpfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
		return (-1);
	unlink("/tmp/tmpfile.txt");
	if (fill_heredoc(delim, fd))
		return (-1);
	return (fd);
}
