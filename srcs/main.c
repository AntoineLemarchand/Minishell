/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/04 11:23:48 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline(const char *prompt);

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_command	**tokens;
	int			i;

	(void)ac;
	(void)av;
	if (env)
	{
		while (1)
		{
			input = readline("MRDSHLL%> ");
			add_history(input);
			if (!input)
			{
				printf("\nexit\n");
				return (0);
			}
			tokens = ft_lexer(input);
			i = 0;
			while (tokens[i])
			{
				printf("CMD:\n");
				printf("[\n");
				printf("\tIN:  %s\n", tokens[i]->infile);
				printf("\tCMD: %s\n", tokens[i]->cmd);
				printf("\tOUT: %s\n", tokens[i]->outfile);
				printf("\tAPPENDMODE: %d\n", tokens[i]->appendmode);
				printf("]\n");
				i++;
			}
		}
	}
	return (0);
}
/*
int	main(void)
{
	char	*inpt;
	int		i;

	i = 0;
	while (i < 10)
	{
		inpt = readline("MRDSHLL%> ");
		add_history(inpt);
		printf("%s", inpt);
		printf("\n");
		++i;
	}
	return (0);
}
*/
