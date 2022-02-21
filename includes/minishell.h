/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:48:25 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/21 11:39:23 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

// states
# define PIPE			0
# define INREDIR		1
# define OUTREDIR		2
# define ALNUM			3
# define LITERAL		4
# define BLANK			5
# define SIMPLEQUOTE	6
# define DOUBLEQUOTE	7
# define VARIABLE		8

typedef struct s_tok {
	char	*val;
	int		type;
}	t_tok;
// lexer_utils.c
void	free_toks(t_tok **toks);
int	toktype(char c);
t_tok **ft_tokalloc(t_tok **toks);
// lexer.c
t_tok	**ft_lex(char *input);
#endif
