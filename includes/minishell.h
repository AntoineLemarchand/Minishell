/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:48:25 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/31 13:09:58 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// echo.c
void	ft_echo(int ac, char **av);
// executils.c
char	*ft_getpath(char *command, char **env);
int		ft_exec(char *action, char **env);
int		ft_fork(int fd, char *action, char **env);
#endif
