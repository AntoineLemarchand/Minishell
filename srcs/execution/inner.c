/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/04 16:25:16 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*built_in_pwd(void)
{
	char	*cwd;

	cwd = ft_calloc(sizeof(char), PATH_MAX + ft_strlen("PWD=") + 1);
	if (!cwd)
		return (NULL);
	strcat(cwd, "PWD=");
	if (!getcwd(&cwd[4], PATH_MAX))
		printf("Mrd! Current WD!");
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
			ft_strlcpy(oldpwd, pwd, ft_strlen(pwd) + 1);
		if (pwd)
		{
			pwd = &pwd[-ft_strlen("PWD=")];
			pwd_ptr = built_in_pwd();
			ft_strlcpy(pwd, pwd_ptr, ft_strlen(pwd_ptr) + 1);
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
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
				printf("Mrd! No more words, just digits!\n");
				g_start->exit = 2;
				return ;
			}
			i++;
		}
		if (cmd[2])
		{
			printf("Mrd! No more that one!\n");
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
