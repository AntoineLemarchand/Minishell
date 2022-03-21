/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:45:21 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/21 12:14:59 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_runinn_cmd(char **cmd, t_env *envcpy, char *temp)
{
	if (!ft_strncmp(cmd[0], "pwd\0", 4))
	{
		temp = built_in_pwd();
		printf("%s\n", &temp[4]);
		free(temp);
	}
	else if (!ft_strncmp(cmd[0], "cd\0", 3))
	{
		if (cmd[0] && cmd[1] && cmd[2])
			ft_putendl_fd("minishell: too many arguments", 2);
		else
			ft_inn_cd(cmd, envcpy, NULL, NULL);
		if (cmd[0] && cmd[1] && cmd[2])
			envcpy->status = 1;
	}
	else if (!ft_strncmp(cmd[0], "env\0", 4))
		ft_inn_env(envcpy);
	else if (!ft_strncmp(cmd[0], "echo\0", 5))
		ft_inn_echo(cmd);
	else if (!ft_strncmp(cmd[0], "exit\0", 5))
		ft_inn_exit(cmd, envcpy);
	else if (!ft_strncmp(cmd[0], "export\0", 7))
		ft_export(cmd, envcpy);
	else if (!ft_strncmp(cmd[0], "unset\0", 6))
		ft_unset(cmd, envcpy);
}

static void	ft_run_cmd(char **cmd, char **env, t_env *envcpy)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_putendl_fd("minishell: fork failed", 2);
	else if (pid > 0)
	{
		free(env);
		waitpid(pid, &envcpy->status, 0);
		envcpy->status = WEXITSTATUS(envcpy->status);
	}
	else if (cmd)
	{
		signal(SIGINT, childprocess);
		if (execve(*cmd, cmd, env) == -1)
			ft_putendl_fd("minishell: execution failed", 2);
		free_data(g_data);
		free(env);
		exit(127);
	}
}

bool	ft_isinn_cmd(char *cmd)
{
	int			i;
	const char	*inn_cmd[]
		= {"pwd\0", "cd\0", "env\0", "echo\0",
		"exit\0", "export\0", "unset\0", NULL};

	i = 0;
	while (inn_cmd[i])
	{
		if (!ft_strncmp(inn_cmd[i], cmd, ft_strlen(cmd) + 1))
			return (true);
		i++;
	}
	return (false);
}

void	ft_runout_cmd(char **cmd, t_env *envcpy)
{
	char	**env;

	env = ft_to_array(envcpy);
	ft_abs_path(cmd, envcpy);
	if (cmd && access(*cmd, F_OK) == 0)
		ft_run_cmd(cmd, env, envcpy);
	else if (cmd)
	{
		envcpy->status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*cmd, 2);
		ft_putendl_fd(": command not found", 2);
		free(env);
	}
	else
		free(env);
	env = NULL;
}

void	ft_run(char	**cmd, t_env *envcpy)
{
	if (cmd && cmd[0] == NULL)
		return ;
	if (cmd && ft_isinn_cmd(cmd[0]))
		ft_runinn_cmd(cmd, envcpy, NULL);
	else
		ft_runout_cmd(cmd, envcpy);
}
