/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:45:21 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/07 19:17:21 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_runinn_cmd(char **cmd, t_env *envcpy)
{
	if (!ft_strncmp(cmd[0], "pwd", 3))
		printf("%s\n", get_env_var("PWD=\0", envcpy) + 4);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		ft_inn_cd(cmd[1], envcpy);
	else if (!ft_strncmp(cmd[0], "env", 3))
		ft_inn_env(envcpy);
	else if (!ft_strncmp(cmd[0], "echo", 4))
		ft_inn_echo(cmd, envcpy);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		ft_inn_exit(cmd, envcpy);
	else if (!ft_strncmp(cmd[0], "export", 6))
		ft_export(cmd, envcpy);
	else if (!ft_strncmp(cmd[0], "unset", 5))
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
		waitpid(pid, &envcpy->status, 0);
		envcpy->status = WEXITSTATUS(envcpy->status);
	}
	else if (cmd)
	{
		if (execve(*cmd, cmd, env) == -1)
			ft_putendl_fd("minishell: execution failed", 2);
		return ;
	}
}

bool	ft_isinn_cmd(char *cmd)
{
	int			i;
	const char	*inn_cmd[]
		= {"pwd", "cd", "env", "echo", "exit", "export", "unset", NULL};

	i = 0;
	while (inn_cmd[i])
	{
		if (!ft_strncmp(inn_cmd[i], cmd, ft_strlen(cmd)))
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
	if (cmd && access(cmd[0], F_OK) == 0)
		ft_run_cmd(cmd, env, envcpy);
	else if (cmd)
	{
		envcpy->status = 127;
		ft_putendl_fd("minishell: command not found", 2);
	}
	free(env);
	env = NULL;
}

void	ft_run(char	**cmd, t_env *envcpy)
{
	ft_change_status(cmd, envcpy);
	if (cmd && cmd[0] == NULL)
		return ;
	if (cmd && ft_isinn_cmd(cmd[0]))
		ft_runinn_cmd(cmd, envcpy);
	else
		ft_runout_cmd(cmd, envcpy);
}
