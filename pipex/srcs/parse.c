/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 00:47:38 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/18 10:35:53 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_fileisvalid(char *path)
{
	if (access(path, F_OK) != 0)
	{
		write(2, "pipex: ", 7);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		write(2, strerror(2), ft_strlen(strerror(2)));
		write(2, "\n", 1);
		exit(2);
	}
	else if (access(path, R_OK) != 0)
	{
		write(2, "pipex: ", 7);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		write(2, strerror(13), ft_strlen(strerror(13)));
		write(2, "\n", 1);
		exit(13);
	}
}

char	*ft_joincommand(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		s1_len;
	int		s2_len;

	if (s1 && s2)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		ret = malloc((s1_len + s2_len + 1) * sizeof(char));
		if (!ret)
			return (NULL);
		i = 0;
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
		i = 0;
		while (s2[i] && s2[i] != ' ')
			ret[s1_len++] = s2[i++];
		ret[s1_len] = '\0';
		return (ret);
	}
	return (NULL);
}
