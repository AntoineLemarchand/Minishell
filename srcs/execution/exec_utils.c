/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:45:21 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/02 15:32:43 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_runinn_cmd(char **cmd)
{
	if (!ft_strncmp(cmd[0], "pwd", 3))
		printf("%s\n", get_env_var("PWD="));
	else if (!ft_strncmp(cmd[0], "cd", 2))
		ft_inn_cd(cmd[1]);
	else if (!ft_strncmp(cmd[0], "env", 3))
		ft_inn_env();
	else if (!ft_strncmp(cmd[0], "echo", 4))
		ft_inn_echo(cmd);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		ft_inn_exit(cmd);
	else if (!ft_strncmp(cmd[0], "export", 6))
		ft_export(cmd);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		ft_unset(cmd);
}

void	ft_run_cmd(char **cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (pid > 0)
	{
		waitpid(pid, &g_start->status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, env) == -1)
			ft_putstr_fd("minishell: command not found\n", 2);
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

void	ft_runout_cmd(char **cmd)
{
	char	**env;

	env = ft_to_array();
	ft_abs_path(cmd);
	if (access(cmd[0], F_OK) == 0)
		ft_run_cmd(cmd, env);
	else
	{
		g_start->status = 127;
		ft_putstr_fd("minishell: command not found\n", 2);
	}
	free(env);
	env = NULL;
}

void	ft_run(char	**cmd)
{
	ft_change_status(cmd);
	if (cmd[0] == NULL)
		return ;
	if (ft_isinn_cmd(cmd[0]))
		ft_runinn_cmd(cmd);
	else
		ft_runout_cmd(cmd);
	ft_free_array(cmd);
}
