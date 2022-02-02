/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:23:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/02 11:38:51 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*tokenize(char *totok, char **env)
{
	int		i;
	char	*cmdtest;

	i = 0;
	cmdtest = ft_getpath(totok, env);
	if (!strncmp(totok, ">>\0>", 3))
		return ("GREATGREAT\0");
	else if (!strncmp(totok, ">\0", 2))
		return ("GREAT\0");
	else if (!strncmp(totok, "<<\0", 3))
		return ("LESSLESS\0");
	else if (!strncmp(totok, "<\0", 2))
		return ("LESS\0");
	else if (!strncmp(totok, "|\0", 2))
		return ("PIPE\0");
	else if (cmdtest)
	{
		free(cmdtest);
		return ("CMD\0");
	}
	else
		return ("WORD\0");
}

char	**lexer(char *inputline, char **env)
{
	int		i;
	int		size;
	char	**ret;
	char	**splitted;

	splitted = ft_split(inputline, ' ');
	size = 0;
	while (splitted[size])
		size++;
	ret = malloc((size + 1) * sizeof(char *));
	i = 0;
	while (splitted[i])
	{
		ret[i] = tokenize(splitted[i], env);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
