/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:09:32 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/17 10:19:05 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	fill_helper(char *temp, t_data *data, int fd)
{
	char	**envcpy;
	char	*input;

	envcpy = convert_env(data->env);
	if (!envcpy)
		return (-1);
	temp = ft_joinfree(temp, "\n");
	if (!temp)
		free(envcpy);
	if (!temp)
		return (-1);
	input = ft_expandval(temp, envcpy, 0);
	free(temp);
	free(envcpy);
	if (!input)
		return (-1);
	write(fd, input, ft_strlen(input));
	free(input);
	return (0);
}

static int	fill_heredoc(char *delim, int fd, t_data *data)
{
	char	*temp;
	int		end;

	end = 0;
	if (dup2(data->env->fdin, 0) == -1)
		return (1);
	while (!end)
	{
		temp = readline("\033[32;1m> \033[0m");
		if (!temp)
		{
			ft_putendl_fd("\nminishell: warning: here-document "
				"delimited by end-of-file", 2);
			end = 1;
		}
		else if (!ft_strncmp(temp, delim, ft_strlen(delim)))
			end = 1;
		else
			end = fill_helper(temp, data, fd);
		if (end == -1)
			return (1);
	}
	return (0);
}

int	ft_heredoc(char *delim, t_data *data)
{
	int		fd;
	int		status;
	pid_t	process;

	process = fork();
	if (process == 0)
	{
		signal(SIGINT, heredoc_process);
		fd = open("/tmp/tmpfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (-1);
		if (fill_heredoc(delim, fd, data))
			return (-1);
		close(fd);
		ft_free_env(data->env);
		free_ast(data->ast_init);
		free(data);
		exit(0);
	}
	waitpid(process, &status, 0);
	data->env->status = WEXITSTATUS(status);
	fd = open("/tmp/tmpfile.txt", O_RDONLY, 0644);
	unlink("/tmp/tmpfile.txt");
	return (fd);
}
