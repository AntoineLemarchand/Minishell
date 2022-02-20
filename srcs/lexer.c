/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:23:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/18 17:49:38 by alemarch         ###   ########.fr       */
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
	toks[size]->value = ft_calloc(2, sizeof(char));
	if (!toks[size]->value)
	{
		free_toks(toks);
		return (NULL);
	}
	*toks[size]->value = input;
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
	toks[size]->value = input;
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
			ret[size]->value = ft_strjoinfree(ret[size]->value, toks[i]->value);
			if (!ret[size]->value)
				free_toks(toks);
			if (!ret[size]->value)
				return (NULL);
		}
		else
		{
			ret = add_tok(ret, ft_strdup(toks[i]->value), toks[i]->type);
			if (size++ && !ret)
				break ;
		}
	}
	return (ret);
}

t_tok	**ft_cleantok(t_tok **toks)
{
	t_tok	**ret;
	int		i;
	int		size;

	i = 0;
	size = -1;
	ret = NULL;
	while (toks[i])
	{
		if (toks[i]->type == BLANK)
			;
		else if (toks[i]->type == VARIABLE)
		{
			i++;
			ret = add_tok(ret, ft_strdup(toks[i]->value), VARIABLE);
			if (size++ && !ret)
				break ;
		}
		else if (toks[i]->type == SIMPLEQUOTE || toks[i]->type == DOUBLEQUOTE)
		{
			i++;
			while (toks[i]->type != ret[size]->type)
			{
				ret[size]->value = ft_strjoinfree(ret[size]->value, toks[i]->value);
				if (!ret[size]->value)
					free_toks(toks);
				if (!ret[size]->value)
					return (NULL);
				i++;
			}
		}
		else
		{
			ret = add_tok(ret, ft_strdup(toks[i]->value), toks[i]->type);
			if (size++ && !ret)
				break ;
			while (toks[i]->type != ret[size]->type)
			{
			}
		}
		i++;
	}
	return (ret);
}

t_tok	**ft_lex(char *input)
{
	int		i;
	t_tok	**toks;
	t_tok	**swp;

	i = 0;
	toks = NULL;
	while (input[i])
	{
		toks = add_char_tok(toks, input[i]);
		if (!toks)
			return (NULL);
		i++;
	}
	swp = toks;
	toks = ft_grouptok(toks);
	free_toks(swp);
	if (!toks)
		return (NULL);
	swp = toks;
	toks = ft_cleantok(toks);
	free_toks(swp);
	if (!toks)
		return (NULL);
	return (toks);
}
