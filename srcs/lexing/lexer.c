/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:23:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 14:09:32 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tok	**add_char_tok(t_tok **toks, char input)
{
	int	size;

	size = 0;
	toks = ft_tokalloc(toks);
	if (!toks)
		return (NULL);
	while (toks[size])
		size++;
	toks[size] = malloc(sizeof(t_tok));
	if (!toks[size])
	{
		free_toks(toks);
		return (NULL);
	}
	toks[size]->val = ft_calloc(2, sizeof(char));
	if (!toks[size]->val)
	{
		free_toks(toks);
		return (NULL);
	}
	*toks[size]->val = input;
	toks[size]->type = toktype(input);
	return (toks);
}

static t_tok	**add_tok(t_tok **toks, char *input, int type)
{
	int	size;

	size = 0;
	toks = ft_tokalloc(toks);
	if (!toks)
		return (NULL);
	while (toks[size])
		size++;
	toks[size] = malloc(sizeof(t_tok));
	if (!toks[size])
	{
		free_toks(toks);
		return (NULL);
	}
	toks[size]->val = input;
	toks[size]->type = type;
	return (toks);
}

static t_tok	**ft_grouptok(t_tok **toks)
{
	t_tok	**ret;
	int		i;
	int		size;

	i = -1;
	size = -1;
	ret = NULL;
	while (toks[++i])
	{
		if (ret && toks[i]->type == ret[size]->type)
		{
			ret[size]->val = ft_joinfree(ret[size]->val, toks[i]->val);
			if (!ret[size]->val)
				return (NULL);
		}
		else
		{
			ret = add_tok(ret, ft_strdup(toks[i]->val), toks[i]->type);
			if (size++ && !ret)
				break ;
		}
	}
	free_toks(toks);
	return (ret);
}

t_tok	**ft_cleantok(t_tok **toks, int i, int size, t_tok **ret)
{
	while (toks[++i])
	{
		if ((toks[i]->type == DOUBLEQUOTE || toks[i]->type == SIMPLEQUOTE)
			&& ft_strlen(toks[i]->val) == 1)
		{
			ret = add_tok(ret, ft_strdup("\0"), toks[i]->type);
			if (size++ && !ret)
				break ;
			while (toks[++i] && toks[i]->type != ret[size]->type)
			{
				ret[size]->val = ft_joinfree(ret[size]->val, toks[i]->val);
				if (!ret[size]->val)
					return (NULL);
			}
		}
		else if (toks[i]->type != BLANK
			&& toks[i]->type != DOUBLEQUOTE && toks[i]->type != SIMPLEQUOTE)
		{
			ret = add_tok(ret, ft_strdup(toks[i]->val), toks[i]->type);
			if (size++ && !ret)
				break ;
		}
	}
	return (ret);
}

t_tok	**ft_lex(char *input)
{
	int		i;
	t_tok	**toks;
	t_tok	**swp;

	if (check_input(input))
		return (NULL);
	i = -1;
	toks = NULL;
	while (input[++i])
	{
		toks = add_char_tok(toks, input[i]);
		if (!toks)
			return (NULL);
	}
	toks = ft_grouptok(toks);
	if (check_toks(toks))
		free_toks(toks);
	if (!toks || check_toks(toks))
		return (NULL);
	swp = toks;
	toks = ft_cleantok(toks, -1, -1, NULL);
	free_toks(swp);
	if (!toks)
		return (NULL);
	return (toks);
}
