/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:30:18 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 14:05:38 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *input)
{
	int		i;
	char	control;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			control = input[i];
			i++;
			while (input[i] && input[i] != control)
				i++;
			if (!input[i])
				return (1);
		}
		i++;
	}
	return (0);
}

static int	check_pipe(char *input)
{
	int		i;

	i = 0;
	while (input[i] == ' ' || (input[i] >= '\t' && input[i] <= '\r'))
		i++;
	if (input[i] == '|')
		return (1);
	i = ft_strlen(input) - 1;
	while (input[i] == ' ' || (input[i] >= '\t' && input[i] <= '\r'))
		i--;
	if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		return (1);
	return (0);
}

int	check_input(char *input)
{
	return (check_quotes(input) || check_pipe(input));
}

int	check_toks(t_tok **toks)
{
	int	i;

	i = 0;
	while (toks[i])
	{
		if ((toks[i]->type == INREDIR || toks[i]->type == OUTREDIR)
			&& ft_strlen(toks[i]->val) > 2)
			return (1);
		i++;
	}
	return (0);
}
