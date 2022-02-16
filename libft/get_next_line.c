/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:38:18 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/16 22:15:52 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
static int	ft_isin(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


static char	*ft_gnl_strjoin(char *temp, char *buffer)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(buffer) + 1));
	if (!result)
		return (NULL);
	while (temp[i])
	{
		result[i] = temp[i];
		i++;
	}
	while (buffer[j])
	{
		result[i + j] = buffer[j];
		j++;
	}
	result[i + j] = '\0';
	free(temp);
	return (result);
}

static char	*ft_read(int fd, char *temp)
{
	int		bread;
	char	*buffer;

	bread = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (ft_isin(temp, '\n') && bread)
	{
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bread] = '\0';
		temp = ft_gnl_strjoin(temp, buffer);
	}
	free(buffer);
	return (temp);
}

static char	*ft_get_line(char *temp)
{
	int		i;
	char	*line;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] && temp[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] && temp[i] == '\n')
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_next(char *temp, char *line)
{
	int		i;
	int		j;
	char	*result;

	j = 0;
	if (!temp[0])
	{
		free(temp);
		return (NULL);
	}
	result = malloc(sizeof(char) * (ft_strlen(temp) - ft_strlen(line) + 1));
	if (!result)
		return (NULL);
	i = ft_strlen(line);
	while (temp[i + j])
	{
		result[j] = temp[i + j];
		j++;
	}
	result[j] = '\0';
	free(temp);
	return (result);
}

char	*gnl(int fd)
{
	static char	*temp;
	char		*line;

	if (!temp)
	{
		temp = malloc(sizeof(char));
		if (!temp)
			return (NULL);
		temp[0] = '\0';
	}
	temp = ft_read(fd, temp);
	line = ft_get_line(temp);
	temp = ft_next(temp, line);
	return (line);
}


int	get_next_line(int fd, char **line)
{
	static char	*temp;

	if (!temp)
	{
		temp = malloc(sizeof(char));
		if (!temp)
			return (0);
		temp[0] = '\0';
	}
	temp = ft_read(fd, temp);
	*line = ft_get_line(temp);
	temp = ft_next(temp, *line);
	if (!*line)
		return (-1);
	return (0);
}
*/

static int	ft_free(char **str, int ret)
{
	free(*str);
	*str = NULL;
	return (ret);
}

static int	ft_check(char **str, char **line)
{
	char	*tmp;
	int		i;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\n')
		{
			if (i == 0)
				*line = ft_strdup("");
			else
				*line = ft_substr(*str, 0, i);
			if (!*line)
				return (-1);
			tmp = *str;
			*str = ft_substr(*str, (i + 1), ft_strlen(*str));
			if (!*str)
				return (-1);
			free(tmp);
			return (1);
		}
	}
	return (0);
}

static int	ft_read(int fd, char *buf, char **str, char **line)
{
	int		bytes;
	char	*tmp;

	bytes = ft_check(str, line);
	if (bytes == -1)
		return (ft_free(str, -1));
	if (bytes)
		return (1);
	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes >= 0)
	{
		buf[bytes] = '\0';
		if (buf[0] == '\0' && ft_strlen(*str))
			continue ;
		else if (buf[0] == '\0' && ft_strlen(*str) <= 0)
			return (ft_free(str, 0));
		tmp = *str;
		*str = ft_strjoin(*str, buf);
		free(tmp);
		bytes = ft_check(str, line);
		if (bytes == -1)
			return (ft_free(str, -1));
		if (bytes)
			return (ft_free(str, 1));
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	*line = ft_substr(*str, 0, ft_strlen(*str));
	if (bytes == -1 || !*line)
		return (ft_free(str, -1));
	return (ft_free(str, 0));
}

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!str)
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (-1);
	}
	return (ft_read(fd, buf, &str, line));
}
