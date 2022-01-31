/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 00:47:14 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/18 10:51:54 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include<unistd.h>
# include<string.h>
# include<stdlib.h>
# include<stdio.h>
# include<fcntl.h>
# include<sys/wait.h>

int		ft_puterror(int errno);
void	ft_fileisvalid(char *path);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *s);
char	**ft_loadcommands(int ac, char **av);
void	ft_freecommands(char **commands);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_joincommand(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	ft_freesplit(char **split);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_fork(int fd, char *action, char **env);
int		ft_exec(char *action, char **env);
#endif
