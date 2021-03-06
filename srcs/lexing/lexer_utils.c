/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:56:55 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/21 11:48:11 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_toks(t_tok **toks)
{
	int	i;

	i = 0;
	while (toks[i])
	{
		free(toks[i]->val);
		free(toks[i]);
		i++;
	}
	free(toks);
}

int	toktype(char c)
{
	if (c == '>')
		return (OUTREDIR);
	else if (c == '<')
		return (INREDIR);
	else if (c == '|')
		return (PIPE);
	else if (c == '\'')
		return (SIMPLEQUOTE);
	else if (c == '"')
		return (DOUBLEQUOTE);
	else if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (BLANK);
	else
		return (LITERAL);
}

t_tok	**ft_tokalloc(t_tok **toks)
{
	int		size;
	t_tok	**ret;

	if (!toks)
	{
		ret = ft_calloc(2, sizeof(t_tok *));
		return (ret);
	}
	size = 0;
	while (toks[size])
		size++;
	ret = ft_calloc(size + 2, sizeof(t_tok *));
	if (!ret)
	{
		free(toks);
		return (NULL);
	}
	size = 0;
	while (toks[size])
	{
		ret[size] = toks[size];
		size++;
	}
	free(toks);
	return (ret);
}

int	hastojoin(int instr, t_tok **toks, int i)
{
	return (instr || (i && toks[i]->type != BLANK && toks[i]->type != OUTREDIR
			&& toks[i]->type != INREDIR && toks[i - 1]->type != BLANK
			&& toks[i - 1]->type != INREDIR
			&& toks[i - 1]->type != OUTREDIR
			&& toks[i]->type != PIPE && toks[i - 1]->type != PIPE));
}

int	is_closing(t_tok *val, char *prev)
{
	int		i;
	int		instr;
	char	control;

	i = 0;
	instr = 0;
	control = '\0';
	while (prev && prev[i])
	{
		if ((prev[i] == '"' || prev[i] == '\'') && !instr)
		{
			instr = 1;
			control = prev[i];
		}
		else if ((prev[i] == '"' || prev[i] == '\'') && prev[i] == control)
			instr = 0;
		i++;
	}
	i = 0;
	if ((instr && control == *val->val) || !instr)
		return (1);
	return (0);
}
