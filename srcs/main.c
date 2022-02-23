/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/23 16:41:32 by alemarch         ###   ########.fr       */
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

/* USED FOR DEBUG
void	printast(t_node	*ast)
{
	int	i;

	if (ast->type == PIPELINE)
	{
		printf("┌PIPE\n");
		printast(((t_pipe *)(ast->node))->left_node);
		printast(((t_pipe *)(ast->node))->right_node);
	}
	else
	{
		printf("├─ CMD\n");
		i = 0;
		while (((t_cmd *)ast->node)->args[i])
		{
			printf("│ └%s\n", ((t_cmd *)(ast->node))->args[i]);
			i++;
		}
		i = 0;
		if (((t_cmd *)ast->node)->redir)
		{
			printf("└── REDIR\n");
			while (((t_cmd *)ast->node)->redir[i])
			{
				printf("    └ %2s - %s\n", ((t_cmd *)ast->node)->redir[i]->type,
					((t_cmd *)ast->node)->redir[i]->val);
				i++;
			}
		}
	}
}
*/

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tok		**tokens;
	t_node		*ast;

	if (!env || ac != 1 || !av)
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
			ast = ft_create_ast(tokens);
			exec_simplecmd(ast, 0, 1);
			free_toks(tokens);
			free_ast(ast);
		}
		free(input);
	}
	rl_clear_history();
	printf("\nexit\n");
	return (0);
}
