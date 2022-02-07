/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/07 10:21:42 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline(const char *prompt);

void	printtok(t_command *token)
{
	printf("SIMPLECMD: \n[\tCMD: %s\n\t"
		"IN: %s\n\tOUT: %s\n\tAPPEND: %d\n]\n",
		token->cmd,
		token->infile,
		token->outfile,
		token->appendmode);
	free_cmd(token);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	int			i;
	t_command	**tokens;

	(void)av;
	if (env && ac == 1)
	{
		while (1)
		{
			input = readline("MRDSHLL%> ");
			add_history(input);
			if (!input)
				break ;
			tokens = ft_lexer(input);
			i = 0;
			while (tokens[i])
				printtok(tokens[i++]);
			free(input);
			free(tokens);
		}
		rl_clear_history();
		printf("\nexit\n");
		return (0);
	}
	return (0);
}
