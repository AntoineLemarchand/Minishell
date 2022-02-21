/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/21 11:39:17 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline(const char *prompt);

static int	ft_isempty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && (s[i] < '\t' || s[i] > '\r'))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	int			i;
	t_tok		**tokens;

	if (!env || ac != 1)
		return (0);
	while (1)
	{
		input = readline("MRDSHLL%> ");
		if (!input)
			break ;
		add_history(input);
		if (!ft_isempty(input))
		{
			tokens = ft_lex(input);
			if (!tokens)
				printf("%s: syntax error\n", av[0]);
			i = -1;
			while (tokens[++i])
				printf("%i: [value: %s - type: %i]\n",
					i, tokens[i]->val, tokens[i]->type);
			free_toks(tokens);
		}
		free(input);
	}
	rl_clear_history();
	printf("\nexit\n");
	return (0);
}
