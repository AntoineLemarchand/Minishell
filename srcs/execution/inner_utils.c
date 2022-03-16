/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:13:50 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/16 15:06:09 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_pwd(t_env *env)
{
	char	**temp;

	temp = malloc(sizeof(char *) * 2);
	temp[0] = NULL;
	temp[1] = built_in_pwd();
	ft_export(temp, env);
	free(temp[1]);
	free(temp);
}

char	*gethome(char *path, t_env *env)
{
	if (!get_env_var("PWD=", env))
		ft_add_pwd(env);
	if ((!path || !ft_strncmp("~\0", path, 2)) && !get_env_var("HOME=", env))
	{
		ft_putendl_fd("minishell: HOME not set", 2);
		env->status = 1;
		return (NULL);
	}
	else if ((!path || !ft_strncmp("~\0", path, 2)) && get_env_var("HOME=", env))
		path = ft_strrchr(get_env_var("HOME=", env), '=') + 1;
	else if (path && !ft_strncmp("~\0", path, 2))
		path = NULL;
	else if (path && !ft_strncmp("-\0", path, 2))
	{
		if (!get_env_var("OLDPWD=", env))
		{
			ft_putendl_fd("minishell: OLDPWD not set", 2);
			env->status = 1;
			return (NULL);
		}
		path = ft_strrchr(get_env_var("OLDPWD=", env), '=') + 1;
		printf("%s\n", &get_env_var("OLDPWD=", env)[7]);
	}
	return (path);
}

void	ft_print_echo(char **cmd, int i)
{
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
	manage_io(link, cmd->redir, 0, g_data);
	ft_runinn_cmd(cmd->args, env, NULL);
	dup2(link[0], 0);
	dup2(link[1], 1);
	close(link[0]);
	close(link[1]);
	return (0);
}
