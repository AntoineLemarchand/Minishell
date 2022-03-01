/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:15:05 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/23 14:20:14 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_size(t_redir	**redir)
{
	int	i;

	i = 0;
	while (redir && redir[i])
		i++;
	return (i);
}

static t_redir	**redir_alloc(t_redir **redir)
{
	int		size;
	t_redir	**ret;

	if (redir)
	{
		size = redir_size(redir);
		ret = ft_calloc(size + 2, sizeof(t_redir *));
		size = 0;
		while (redir[size])
		{
			ret[size] = redir[size];
			size++;
		}
	}
	else
		ret = ft_calloc(2, sizeof(t_redir *));
	return (ret);
}

t_redir	**ft_addredir(t_redir **redir, t_tok **tokens)
{
	t_redir	**ret;
	int		size;

	ret = redir_alloc(redir);
	size = redir_size(redir);
	if (tokens[1])
	{
		ret[size] = malloc(sizeof(t_redir));
		ret[size]->type = ft_strdup(tokens[0]->val);
		ret[size]->val = ft_strdup(tokens[1]->val);
	}
	else
		ret = NULL;
	if (redir)
		free(redir);
	return (ret);
}

static char	**args_alloc(char	**args)
{
	char	**ret;
	int		size;

	size = 0;
	while (args && args[size])
		size++;
	if (!size)
		ret = ft_calloc(2, sizeof(char *));
	else
		ret = ft_calloc(size + 2, sizeof(char *));
	size = 0;
	while (args && args[size])
	{
		ret[size] = args[size];
		size++;
	}
	return (ret);
}

char	**ft_addargs(char	**args, t_tok	*tok)
{
	char	**ret;
	int		size;

	ret = args_alloc(args);
	size = 0;
	while (args && args[size])
		size++;
	ret[size] = ft_strdup(tok->val);
	if (args)
		free(args);
	if (!ret[size])
	{
		ft_freesplit(ret);
		return (NULL);
	}
	return (ret);
}
