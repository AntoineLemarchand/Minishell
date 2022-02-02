/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:48:25 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/02 11:29:26 by alemarch         ###   ########.fr       */
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

// executils.c
char	*ft_joincommand(char *s1, char *s2);
void	ft_freesplit(char **split);
// lexer.c
char	**lexer(char *inputline, char **env);
// pipe.c
int		ft_exec(char *action, char **env);
int		ft_fork(int fd, char *action, char **env);
char	*ft_getpath(char *command, char **env);
// echo.c
void	ft_echo(int ac, char **av);
#endif
