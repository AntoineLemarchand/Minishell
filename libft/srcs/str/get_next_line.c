/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 21:40:15 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/25 12:44:09 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_loadstatic(int fd, char **remain)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read && !ft_strchr(remain[fd], '\n'))
	{
		tmp = malloc(BUFFER_SIZE + 1);
		if (!tmp)
			return (1);
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(tmp);
			return (1);
		}
		tmp[bytes_read] = '\0';
		if (remain[fd])
			remain[fd] = ft_joinfree(remain[fd], tmp);
		else
			remain[fd] = ft_strdup(tmp);
		if (!remain[fd])
			return (1);
		free(tmp);
	}
	return (0);
}

static int	ft_update_remain(int fd, char **remain, int newline_index)
{
	char	*newremain;

	newremain = ft_substr(remain[fd], newline_index + 1, ft_strlen(remain[fd]));
	if (!newremain)
		return (1);
	free(remain[fd]);
	remain[fd] = newremain;
	return (0);
}

static char	*ft_getline(int fd, char **remain)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (remain[fd] && remain[fd][i] && remain[fd][i] != '\n')
		i++;
	if (remain[fd] && ft_strlen(remain[fd]) == i)
	{
		ret = ft_strdup(remain[fd]);
		if (!ret)
			return (NULL);
		free(remain[fd]);
		remain[fd] = NULL;
		return (ret);
	}
	ret = ft_substr(remain[fd], 0, i + 1);
	if (!ret)
		return (NULL);
	if (ft_update_remain(fd, remain, i))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*remain[1024];
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_loadstatic(fd, remain))
		return (NULL);
	buff = ft_getline(fd, remain);
	if (buff[0] == '\0')
	{
		free(buff);
		free(remain[fd]);
		return (NULL);
	}
	return (buff);
}
