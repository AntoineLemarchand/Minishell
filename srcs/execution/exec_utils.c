/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:45:21 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/03 16:30:06 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_runinn_cmd(char **cmd, t_env *g_start)
{
	if (!ft_strncmp(cmd[0], "pwd", 3))
		printf("%s\n", get_env_var("PWD=", g_start));
	else if (!ft_strncmp(cmd[0], "cd", 2))
		ft_inn_cd(cmd[1], g_start);
	else if (!ft_strncmp(cmd[0], "env", 3))
		ft_inn_env(g_start);
	else if (!ft_strncmp(cmd[0], "echo", 4))
		ft_inn_echo(cmd, g_start);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		ft_inn_exit(cmd, g_start);
	else if (!ft_strncmp(cmd[0], "export", 6))
		ft_export(cmd, g_start);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		ft_unset(cmd, g_start);
}

static void	ft_run_cmd(char **cmd, char **env, t_env *g_start)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("Mrd! Fork!\n");
	else if (pid > 0)
	{
		waitpid(pid, &g_start->status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, env) == -1)
			printf("Mrd! Shell!\n");
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

void	ft_runout_cmd(char **cmd, t_env *g_start)
{
	char	**env;

	env = ft_to_array(g_start);
	ft_abs_path(cmd, g_start);
	if (access(cmd[0], F_OK) == 0)
		ft_run_cmd(cmd, env, g_start);
	else
	{
		g_start->status = 127;
		printf("Mrd! Command not found!\n");
	}
	free(env);
	env = NULL;
}

void	ft_run(char	*input, t_env *g_start)
{
	char	**cmd;

	cmd = ft_split(input, ' ');
	free(input);
	input = (char *) NULL;
	ft_change_status(cmd, g_start);
	if (cmd[0] == NULL)
		return ;
	if (ft_isinn_cmd(cmd[0]))
		ft_runinn_cmd(cmd, g_start);
	else
		ft_runout_cmd(cmd, g_start);
	ft_free_array(cmd);
}
