/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/16 13:25:33 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_copy *copy, int i)
{
	free_cmdarg(copy);
	if (g_envs)
		ft_free_array(g_envs);
	if (copy->list)
		free_list(copy->list);
	if (copy->cmdssep)
		free(copy->cmdssep);
	if (!g_tester && i == 1)
		ft_putstr_fd("A tout!\n", 2);
	exit(g_status);
}

int	return_error(char *cmd, char *msg, int ret, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	if (status >= 0)
		g_status = status;
	return (ret);
}

int	check_space_colon(char *line)
{
	size_t	i;
	int		colon;

	colon = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == ':' && colon)
			|| (!ft_isspace(line[i]) && line[i] != ':'))
			return (0);
		if (line[i] == ':')
			colon = 1;
		i++;
	}
	return (1);
}

void	prompt(void)
{
	ft_putstr_fd("\033[32;1m", 1);
	ft_putstr_fd("MrdShll", 1);
	ft_putstr_fd(">\033[0m ", 1);
}

int	main(int argc, char **argv, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	g_envs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!g_envs)
		return (0);
	i = 0;
	while (envp[i])
	{
		g_envs[i] = ft_strdup(envp[i]);
		i++;
	}
	g_envs[i] = 0;
	if (argc >= 2)
	{
		if (argv[1][0] == '-' && argv[1][1] == 'c' && argv[2])
			loop_tester(argv[2]);
		else
			return_error(argv[1], ": No such file or directory\n", 0, 127);
	}
	else
		loop();
	return (0);
}
