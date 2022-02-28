/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/28 16:54:54 by alemarch         ###   ########.fr       */
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

/*
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

int	exec_line(t_node *ast, char **env)
{
	int	fdin;
	int	fdout;

	fdin = dup(0);
	fdout = dup(1);
	if (fdin == -1 || fdout == -1)
		return (1);
	exec_simplecmd(ast, env);
	if (dup2(fdin, 0) == -1 || dup2(fdout, 1) == -1)
		return (1);
	return (0);
}

t_node	*parse_input(char *input, char **env)
{
	t_tok	**tokens;
	t_node	*ret;

	tokens = ft_lex(input);
	if (!tokens)
		return (NULL);
	if (ft_expand(tokens, env))
	{
		free_toks(tokens);
		return (NULL);
	}
	ret = ft_create_ast(tokens);
	free_toks(tokens);
	if (!ret)
		return (NULL);
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_node		*ast;

	(void)ac;
	while (1)
	{
		input = readline("MRDSHLL%> ");
		if (!input)
			break ;
		add_history(input);
		if (!ft_isempty(input))
		{
			ast = parse_input(input, env);
			if (!ast)
				printf("%s: \"%s\": syntax error\n", av[0], input);
			else
			{
				exec_line(ast, env);
				free_ast(ast);
			}
		}
		free(input);
	}
	rl_clear_history();
	printf("\nexit\n");
	return (0);
}
