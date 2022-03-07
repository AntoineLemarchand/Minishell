/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:09:32 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/06 18:24:32 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	fill_heredoc(char *delim, int fd, char **env)
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
			temp = ft_joinfree(temp, "\n");
			input = ft_expandval(temp, env);
			if (!input)
				return (1);
			write(fd, input, ft_strlen(input));
			free(input);
		}
		free(temp);
	}
	return (0);
}

int	ft_heredoc(char *delim, char **env)
{
	int		fd;
	pid_t	process;

	process = fork();
	if (process == 0)
	{
		fd = open("tmpfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (!fd)
			return (-1);
		if (fill_heredoc(delim, fd, env))
			return (-1);
		close(fd);
		ft_freesplit(env);
		free(delim);
		exit(0);
	}
	waitpid(process, NULL, 0);
	fd = open("tmpfile.txt", O_RDONLY, 0644);
	unlink("tmpfile.txt");
	return (fd);
}
