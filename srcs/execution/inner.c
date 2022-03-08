/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/08 14:49:29 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*built_in_pwd(void)
{
	char	*cwd;

	cwd = ft_calloc(sizeof(char), PATH_MAX + ft_strlen("PWD=\0") + 1);
	if (!cwd)
		return (NULL);
	strcat(cwd, "PWD=");
	if (!getcwd(&cwd[4], PATH_MAX))
		ft_putendl_fd("Mrd! Current WD!", 2);
	return (cwd);
}

void	ft_inn_cd(char *path, t_env *g_start)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;

	if (!path)
		return ;
	if (!chdir(path))
	{
		pwd = ft_strrchr(get_env_var("PWD=", g_start), '=') + 1;
		oldpwd = ft_strrchr(get_env_var("OLDPWD=", g_start), '=') + 1;
		if (oldpwd && pwd)
			oldpwd = ft_strdup(pwd);
		if (pwd)
		{
			pwd = &pwd[-ft_strlen("PWD=")];
			pwd_ptr = built_in_pwd();
			pwd = ft_strdup(pwd_ptr);
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
		free(oldpwd);
		free(pwd);
	}
	else
		printf("Mrd! Chdir!\n");
}

void	ft_inn_env(t_env *g_start)
{
	t_env	*temp;

	temp = g_start;
	while (temp)
	{
		printf("%s\n", temp->var);
		temp = temp->next;
	}
}

void	ft_inn_exit(char **cmd, t_env *g_start)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmd[0], "exit", 4) && cmd[1])
	{
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				ft_putendl_fd("minishell: numeric argument required", 2);
				g_start->exit = 2;
				return ;
			}
			i++;
		}
		if (cmd[2])
		{
			ft_putendl_fd("minishell: too many arguments", 2);
				g_start->exit = 2;
			return ;
		}
		g_start->exit = ft_atoi(cmd[1]);
	}
	else if (!ft_strncmp(cmd[0], "exit", 4))
		g_start->exit = 0;
}

void	ft_inn_echo(char **cmd, t_env *envcpy)
{
	if (!ft_strncmp(cmd[0], "echo", 4) && cmd[1] && cmd[1][0] == '$')
	{
		if (!ft_strncmp(&cmd[1][1], get_env_var(&cmd[1][1], envcpy), 4)
				&& get_env_var(&cmd[1][1],
				envcpy)[ft_strlen(cmd[1]) - 1] == '=')
			printf("%s\n", &get_env_var(&cmd[1][1], envcpy)[ft_strlen(cmd[1])]);
		else
			printf("Mrd! Are you sure with this name?!\n");
	}
	else if (!ft_strncmp(cmd[0], "echo", 4) && cmd[1]
		&& ft_strncmp(cmd[1], "-n", 2))
	{
		ft_print_echo(cmd, 1);
		printf("\n");
	}
	else if (!ft_strncmp(cmd[0], "echo", 4) && cmd[1] && cmd[2]
		&& !ft_strncmp(cmd[1], "-n", 2))
		ft_print_echo(cmd, 2);
}
