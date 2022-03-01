/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:12:07 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/23 16:08:11 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_pipe(t_tok **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == PIPE)
			return (i);
		i++;
	}
	return (0);
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static int	ft_parsecmd(t_node *ast, t_tok **tokens)
{
	int		i;
	t_cmd	*ret;

	i = 0;
	ret = malloc(sizeof(t_cmd));
	ret->args = NULL;
	ret->redir = NULL;
	while (tokens[i])
	{
		if (tokens[i]->type == INREDIR || tokens[i]->type == OUTREDIR)
		{
			ret->redir = ft_addredir(ret->redir, tokens + i);
			i++;
		}
		else
			ret->args = ft_addargs(ret->args, tokens[i]);
		i++;
	}
	ast->type = SIMPLECMD;
	ast->node = ret;
	return (0);
}

t_node	*ft_create_ast(t_tok	**tokens);

static int	ft_parsepipe(t_node	*ast, t_tok	**tokens, int index)
{
	t_tok	**tokleft;
	t_tok	**tokright;
	t_pipe	*ret;

	tokleft = getleft(tokens, index);
	tokright = getright(tokens, index);
	if (!tokright || !tokleft)
		return (1);
	ret = malloc(sizeof(t_pipe));
	ret->left_node = ft_create_ast(tokleft);
	free_toks(tokleft);
	ret->right_node = ft_create_ast(tokright);
	free_toks(tokright);
	if (!ret->left_node || !ret->right_node)
		return (1);
	ast->type = PIPELINE;
	ast->node = ret;
	return (0);
}

t_node	*ft_create_ast(t_tok	**tokens)
{
	t_node	*ret;

	ret = malloc(sizeof(t_node));
	if (!has_pipe(tokens))
		ft_parsecmd(ret, tokens);
	else
		(ft_parsepipe(ret, tokens, has_pipe(tokens)));
	return (ret);
}
