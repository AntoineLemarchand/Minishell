/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 19:18:30 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/10 16:54:48 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freecommands(char **commands)
{
	char	**commandsbegin;

	commandsbegin = commands;
	while (*commands)
	{
		free(*commands);
		commands++;
	}
	free(commandsbegin);
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
