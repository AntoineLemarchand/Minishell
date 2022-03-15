/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/15 10:53:34 by alemarch         ###   ########.fr       */
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
		ft_putendl_fd("minishell: already in working directory", 2);
	return (cwd);
}

void	ft_inn_cd(char **cmd, t_env *env, char *oldpwd, char *pwd)
{
	char	*pwd_ptr;
	char	*path;

	path = gethome(cmd[1], env, NULL);
	if (!path)
		return ;
	if (!chdir(path))
	{
		pwd = ft_strrchr(get_env_var("PWD=", env), '=') + 1;
		oldpwd = ft_strrchr(get_env_var("OLDPWD=", env), '=') + 1;
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
		return ;
	}
	ft_putendl_fd("minishell: No such file or directory", 2);
	env->status = 1;
}

/*
void	ft_export_pwd(char **cmd, t_env *g_start)
{
	int		i;
	char	*str;
	char	*name;

	i = 0;
	name = NULL;
	while (cmd[1] && cmd[1][i] && cmd[1][i] != '=')
		i++;
	if (!cmd[1][i])
		return ;
	name = ft_calloc(sizeof(char), i + 2);
	if (!name)
		return ;
	ft_strlcpy(name, cmd[1], i + 2);
	if (get_env_var(name, g_start))
	{
		str = ft_strrchr(get_env_var(name, g_start), '=') + 1;
		str = &str[-ft_strlen(name)];
		ft_strlcpy(str, cmd[1], ft_strlen(cmd[1]) + 1);
	}
	else
		ft_add_env(ft_strdup(cmd[1]), g_start);
	free(name);
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
			ft_add_env(built_in_pwd(), g_start);
			//strcpy(pwd, built_in_pwd() + 4);
			//printf("pwd: %s\n", pwd);
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
*/

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

	i = -1;
	if (!ft_strncmp(cmd[0], "exit", 4) && cmd[1])
	{
		while (cmd[1][++i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				ft_putendl_fd("minishell: numeric argument required", 2);
				g_start->exit = 2;
				return ;
			}
		}
		if (cmd[2])
		{
			ft_putendl_fd("minishell: too many arguments", 2);
			g_start->status = 1;
			return ;
		}
		g_start->exit = ft_atoi(cmd[1]);
	}
	else if (!ft_strncmp(cmd[0], "exit", 4))
		g_start->exit = g_start->status;
	g_start->status = g_start->exit;
}

void	ft_inn_echo(char **cmd)
{
	int	i;

	i = 2;
	if (!ft_strncmp(cmd[0], "echo", 4) && cmd[1]
		&& ft_strncmp(cmd[1], "-n", 2))
	{
		ft_print_echo(cmd, 1);
		printf("\n");
	}
	else if (!ft_strncmp(cmd[0], "echo", 4) && cmd[1] && cmd[2]
		&& !ft_strncmp(cmd[1], "-n", 2))
	{
		while (!ft_strncmp(cmd[i], "-n", 2))
			i++;
		ft_print_echo(cmd, i);
	}
	g_data->env->status = 0;
}
