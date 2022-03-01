/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:42:28 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/23 15:17:32 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	**getleft(t_tok **tokens, int index)
{
	t_tok	**ret;
	int		i;

	ret = ft_calloc(index + 1, sizeof(t_tok *));
	i = 0;
	while (i < index)
	{
		ret[i] = malloc(sizeof(t_tok));
		ret[i]->type = tokens[i]->type;
		ret[i]->val = ft_strdup(tokens[i]->val);
		if (!ret[i]->val)
		{
			free_toks(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

t_tok	**getright(t_tok **tokens, int index)
{
	t_tok	**ret;
	int		i;
	int		size;

	size = 0;
	while (tokens[size])
		size++;
	ret = ft_calloc(size - index + 1, sizeof(t_tok *));
	i = index + 1;
	while (i < size)
	{
		ret[i - index - 1] = malloc(sizeof(t_tok));
		ret[i - index - 1]->type = tokens[i]->type;
		ret[i - index - 1]->val = ft_strdup(tokens[i]->val);
		if (!ret[i - index - 1]->val)
		{
			free_toks(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

void	free_cmd(t_cmd	*cmd)
{
	int	i;

	i = 0;
	while (cmd->redir && cmd->redir[i])
	{
		free(cmd->redir[i]->type);
		free(cmd->redir[i]->val);
		free(cmd->redir[i]);
		i++;
	}
	if (cmd->redir)
		free(cmd->redir);
	if (cmd->args)
		ft_freesplit(cmd->args);
	free(cmd);
}

void	free_ast(t_node *ast)
{
	if (ast->type == PIPELINE)
	{
		free_ast(((t_pipe *)ast->node)->left_node);
		free_ast(((t_pipe *)ast->node)->right_node);
		free(ast->node);
	}
	else
		free_cmd((t_cmd *)ast->node);
	free(ast);
}
