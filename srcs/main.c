/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/01/31 13:05:20 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline(const char *prompt);

void	ft_merde(void)
{
	printf("Merde!");
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	(void)ac;
	(void)av;
	(void)env; // to secure

	while (1)
	{
		input =	readline("MRDSHLL%>");
		add_history(input);
		printf("%s\n",input);
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
