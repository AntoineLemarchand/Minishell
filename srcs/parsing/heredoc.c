/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:09:32 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/03 09:55:59 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_heredoc(char *delim)
{
	char	*input;
	char	*temp;
	int		end;
	int		fd;

	end = 0;
	fd = open("tmpfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	unlink("tmpfile.txt");
	while (!end)
	{
		temp = readline("\033[32;1m>\033[0m");
		if (!ft_strncmp(temp, delim, ft_strlen(delim)))
			end = 1;
		else
		{
			input = ft_strjoin(temp, "\n");
			write(fd, input, ft_strlen(input));
			free(input);
		}
		free(temp);
	}
	return (fd);
}
