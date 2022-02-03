/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/03 11:54:56 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isinn_cmd(char *cmd)
{
	if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
		return (true);
	else if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return (true);
	else if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
		return (true);
	else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
		return (true);
	else if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
		return (true);
	else if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
		return (true);
	else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
		return (true);
	else
		return (false);
}

static char	*ft_env_var(char *var, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (ft_strdup(&env[i][ft_strlen(var)]));
		i++;
	}
	return (NULL);
}

static char	*ft_pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * PATH_MAX + 5);//strlen("PWD=") + 1
	if (!cwd)
		return (NULL);
	ft_strlcat(cwd, "PWD=", (ft_strlen(cwd) + 4));
	if (!getcwd(&cwd[4], PATH_MAX)) 
		printf("MRD! getcwd\n");
	return (cwd);
}

static void	ft_inn_cd(char *path, char **env)
{
	char	*oldpwd = NULL;
	char	*pwd = NULL;
	char	*pwd_ptr = NULL;

	if (!path)
		return;
	if (!chdir(path))
	{//SGFT inside this loop
		pwd = ft_strrchr(ft_env_var("PWD=", env), '=') + 1;
		oldpwd = ft_strrchr(ft_env_var("OLDPWD=", env), '=') + 1;
		if (oldpwd && pwd) 
			ft_strlcpy(oldpwd, pwd, ft_strlen(pwd));
		if (pwd) 
		{
			pwd = &pwd[-4];//-ft_strlen("PWD=")
			pwd_ptr = ft_pwd();
			ft_strlcpy(pwd, pwd_ptr, ft_strlen(pwd_ptr));
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
	}
	else
		printf("Mrd! chdir\n");
}

static void	ft_runinn_cmd(char **cmd, char **env)
{
	if (!ft_strncmp("cd", cmd[0], ft_strlen(cmd[0])))
		ft_inn_cd(cmd[1], env);
	else if (!ft_strncmp("echo", cmd[0], ft_strlen(cmd[0])))
		printf("inn echo\n");
	else if (!ft_strncmp("env", cmd[0], ft_strlen(cmd[0])))
		printf("inn env\n");
	else if (!ft_strncmp("exit", cmd[0], ft_strlen(cmd[0])))
		printf("inn exit\n");
	else if (!ft_strncmp("export", cmd[0], ft_strlen(cmd[0])))
		printf("inn export\n");
	else if (!ft_strncmp("pwd", cmd[0], ft_strlen(cmd[0])))
		printf("MRD_PWD=%s\n", ft_env_var("PWD=", env));
	else if (!ft_strncmp("unset", cmd[0], ft_strlen(cmd[0])))
		printf("inn unset\n");
}

static bool	ft_abs_path(char **cmd, char **env)
{
	char	*path;
	char	*bin;
	char	**path_split;
	size_t	idx;
	int		i;

	idx = 0;
	bin = NULL;
	path = NULL;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		i = 0;
		while (env[i])
		{
			if (!ft_strncmp(env[i], "PATH=", 5))
			{
				path = ft_strdup(&env[i][5]);
				break ;
			}
			i++;
		}
		if (!path)
			return (false);
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		while (path_split[idx])
		{
			bin = malloc((ft_strlen(path_split[idx]) + ft_strlen(cmd[0]) + 2));
			if (bin == NULL)
				break ;
			ft_strlcat(bin, path_split[idx], (ft_strlen(bin) \
						+ ft_strlen(path_split[idx]) + 1));
			ft_strlcat(bin, "/", (ft_strlen(bin) + 2));
			ft_strlcat(bin, cmd[0], (ft_strlen(bin) + ft_strlen(cmd[0]) + 1));
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
			idx++;
		}
		//todo free_all(path_split);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
	if (!bin)
		return (false);
	return (true);
}

static void	ft_run_cmd(char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		printf("Mrd!\n");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, env) == -1)
			printf("Mrd!\n");
		exit(0);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	char	**cmd;

	(void)argc;
	(void)argv;
	input = (char *)malloc(sizeof(char) * 1024);
	if (!input)
		return (0);
	while (1)
	{
		input = readline("MRDSHLL>");
		add_history(input);
		// try to split with 32
		cmd = ft_split(input, ' ');
		if (!cmd[0])
			printf("Mrd! Command not found!\n");
		// Check if this cmd is local for the our shell
		else if (ft_isinn_cmd(cmd[0]))
			// Run local cmd
			ft_runinn_cmd(cmd, env);
		else
		{
			// Check th epath from env for run the shell cmd
			if (ft_abs_path(cmd, env))
				// Run shell cmd
				ft_run_cmd(cmd, env);
			else
				printf("Mrd! Command not found!\n");
			//free(env);
		}
		//free(cmd);
	}
	//ft_free_all();
	printf("A tout!\n");
	return (0);
}
