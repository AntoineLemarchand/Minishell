/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:13:50 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/24 11:23:24 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_pwd(t_env *env, int old)
{
	char	**temp;
	char	*swap;

	temp = malloc(sizeof(char *) * 2);
	temp[0] = NULL;
	if (!old)
		temp[1] = built_in_pwd();
	else
	{
		swap = built_in_pwd();
		temp[1] = ft_strjoin("OLD", swap);
		free(swap);
	}
	ft_export(temp, env);
	free(temp[1]);
	free(temp);
}

void	ft_add_del(char *path, t_env *env)
{
	if (!get_env_var("PWD", env))
		ft_add_pwd(env, 0);
	if (path && ft_strncmp("-\0", path, 2) && !get_env_var("OLDPWD", env))
		ft_add_pwd(env, 1);
}

char	*gethome(char *path, t_env *env)
{
	ft_add_del(path, env);
	if ((!path || !ft_strncmp("~\0", path, 2)) && !get_env_var("HOME", env))
	{
		ft_putendl_fd("minishell: HOME not set", 2);
		env->status = 1;
		return (NULL);
	}
	else if ((!path || !ft_strncmp("~\0", path, 2)) && get_env_var("HOME", env))
		path = ft_strrchr(get_env_var("HOME", env), '=') + 1;
	else if (path && !ft_strncmp("~\0", path, 2))
		path = NULL;
	else if (path && !ft_strncmp("-\0", path, 2))
	{
		if (!get_env_var("OLDPWD", env))
		{
			ft_putendl_fd("minishell: OLDPWD not set", 2);
			env->status = 1;
			ft_add_pwd(env, 1);
			return (NULL);
		}
		path = ft_strrchr(get_env_var("OLDPWD", env), '=') + 1;
		printf("%s\n", &get_env_var("OLDPWD", env)[7]);
	}
	return (path);
}

void	ft_print_echo(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (!ft_strncmp(cmd[i], "-n", 2) && j == (int)ft_strlen(cmd[i]))
			i++;
		else
			break ;
		j = 1;
	}
	while (cmd && cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
}

int	exec_singlebuiltin(t_cmd *cmd, t_env *env)
{
	int		link[2];

	link[0] = dup(0);
	if (link[0] == -1)
		return (1);
	link[1] = dup(0);
	if (link[0] == -1)
	{
		close(link[0]);
		return (1);
	}
	if (manage_io(link, cmd->redir, 0, g_data) != 2)
		ft_runinn_cmd(cmd->args, env, NULL);
	else
		g_data->env->status = 2;
	dup2(link[0], 0);
	dup2(link[1], 1);
	close(link[0]);
	close(link[1]);
	return (0);
}
