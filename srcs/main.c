/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/14 17:28:41 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//   Run it witout Makefile
//   gcc -I../includes  main.c -lreadline ../libft/libft.a


//#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <pwd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>


int rl_bind_key (int key, rl_command_func_t *function);
void rl_clear_history (void);


typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

static t_env	*g_start = NULL;

static char	*built_in_pwd(void)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * PATH_MAX + strlen("PWD=") + 1);
	if (!cwd)
		return (NULL);
	strcat(cwd, "PWD=");
	if (!getcwd(&cwd[4], PATH_MAX))
		printf("Mrd! Current WD!");
	return (cwd);
}

static char	*get_env_var(char *var)
{
	t_env	*temp;
	size_t	size;

	temp = g_start;
	size = ft_strlen(var);
	while (temp)
	{
		if (!ft_strncmp(var, temp->var, size))
			return (temp->var);
		temp = temp->next;
	}
	return (NULL);
}

static void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

static void	ft_run_cmd(char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		printf("Mrd! Fork!\n");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, env) == -1)
			printf("Mrd! Shell!\n");
		exit(EXIT_FAILURE);
	}
}

static bool	ft_abs_path(char **cmd, char **env)
{
	char	*path;
	char	*bin;
	char	**path_split;
	size_t	i;
	int		j;

	i = 0;
	bin = NULL;
	path = NULL;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		j = 0;
		while (env[j])
		{
			if (!ft_strncmp(env[j], "PATH=", 5))
			{
				path = ft_strdup(&env[j][5]);
				break ;
			}
			j++;
		}
		if (!path)
			return (false);
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		while (path_split[i])
		{
			bin = malloc((ft_strlen(path_split[i]) + ft_strlen(cmd[0]) + 2));
			if (bin == NULL)
				break ;
			ft_strlcat(bin, path_split[i], (ft_strlen(bin) \
						+ ft_strlen(path_split[i]) + 1));
			ft_strlcat(bin, "/", (ft_strlen(bin) + 2));
			ft_strlcat(bin, cmd[0], (ft_strlen(bin) + ft_strlen(cmd[0]) + 1));
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
			i++;
		}
		ft_free_array(path_split);
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

static bool	ft_isinn_cmd(char *cmd)
{
	int			i;
	const char	*inn_cmd[] = {"pwd", "cd", "env", "echo", "exit", NULL};

	i = 0;
	while (inn_cmd[i])
	{
		if (!ft_strncmp(inn_cmd[i], cmd, ft_strlen(cmd)))
			return (true);
		i++;
	}
	return (false);
}

static void	ft_inn_cd(char *path)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;

	if (!path)
		return ;
	if (!chdir(path))
	{
		pwd = ft_strrchr(get_env_var("PWD="), '=') + 1;
		oldpwd = ft_strrchr(get_env_var("OLDPWD="), '=') + 1;
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

static void	ft_inn_env(void)
{
	t_env	*temp;

	temp = g_start;
	while (temp)
	{
		printf("%s\n", temp->var);
		temp = temp->next;
	}
}

static void	ft_inn_echo(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 4) && cmd[1] && cmd[1][0] == '$')
		printf("%s\n", get_env_var(&cmd[1][1]));
	else if (!ft_strncmp(cmd[0], "echo", 4) && cmd[1] && ft_strncmp(cmd[1], "-n", 2))
		printf("%s\n", cmd[1]);
	else if (!ft_strncmp(cmd[0], "echo", 4) && cmd[1] && cmd[2] && !ft_strncmp(cmd[1], "-n", 2))
		printf("%s", cmd[2]);

}

static void	ft_free_env(void)
{
	t_env	*i;
	t_env	*temp;

	i = g_start;
	temp = i;
	while (i)
	{
		temp = i;
		i = i->next;
		free(temp->var);
		temp->var = NULL;
		free(temp);
		temp = NULL;
	}
}

static int	ft_exit(char **cmd, char *input)
{
	free(input);
	ft_free_array(cmd);
	ft_free_env();
	rl_clear_history();
	printf("Putain de merde! A tout!\n");
	exit (0);
}

static void	ft_runinn_cmd(char **cmd, char *input)
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
		ft_exit(cmd, input);
}

static void	ft_add_env(char *var)
{
	t_env	*ptr;
	t_env	*new_node;

	ptr = g_start;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		printf("Mrd! Malloc fail!\n");
		return ;
	}
	new_node->var = var;
	new_node->next = NULL;
	if (!ptr)
		g_start = new_node;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}

static void	ft_add_var(char *var)
{
	struct passwd	*pw;
	char			*result;

	pw = getpwuid(getuid());
	if (!ft_strncmp(var, "HOME", 4))
	{
		result = malloc(sizeof(char) * (ft_strlen(pw->pw_dir) + 6));
		if (!result)
		{
			printf("Mrd! Cannot add HOME!\n");
			return ;
		}
		ft_strlcat(result, "HOME=", ft_strlen(result) + 6);
		ft_strlcat(result, pw->pw_dir, ft_strlen(result) \
				+ ft_strlen(pw->pw_dir));
	}
	else if (!ft_strncmp(var, "PATH", 4))
	{
		result = ft_strdup("PATH=/bin:/usr/bin");
		if (!result)
		{
			printf("Mrd! Cannot add PATH!\n");
			return ;
		}
	}
	else if (!ft_strncmp(var, "OLDPWD", 6))
	{
		result = ft_strdup("OLDPWD=");
		if (!result)
		{
			printf("Mrd! Cannot add OLDPWD!\n");
			return ;
		}
	}
	else if (!ft_strncmp(var, "PWD", 3))
	{
		result = built_in_pwd();
		if (!result)
		{
			printf("Mrd! Cannot add PWD!\n");
			return ;
		}
	}
	else if (!ft_strncmp(var, "SHLVL", 5))
	{
		result = ft_strdup("SHLVL=1");
		if (!result)
		{
			printf("Mrd! Cannot add OLDPWD!\n");
			return ;
		}
	}
	ft_add_env(result);
}

static void	ft_make_env(char **envp)
{
	char	*var_list[6];
	int		i;
	int		size;

	i = 0;
	size = 5;
	var_list[0] = "PATH";
	var_list[1] = "HOME";
	var_list[2] = "OLDPWD";
	var_list[3] = "PWD";
	var_list[4] = "SHLVL";
	var_list[5] = NULL;
	while (envp[i])
	{
		ft_add_env(ft_strdup(envp[i]));
		if (!ft_strncmp(envp[i], "PATH", 4))
			var_list[0] = NULL;
		else if (!ft_strncmp(envp[i], "HOME", 4))
			var_list[1] = NULL;
		else if (!ft_strncmp(envp[i], "OLDPWD", 6))
			var_list[2] = NULL;
		else if (!ft_strncmp(envp[i], "PWD", 3))
			var_list[3] = NULL;
		else if (!ft_strncmp(envp[i], "SHLVL", 5))
			var_list[4] = NULL;
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (var_list[i])
			ft_add_var(var_list[i]);
		i++;
	}
}

static char	**ft_to_array(void)
{
	char	**result;
	t_env	*temp;
	size_t	i;

	i = 0;
	temp = g_start;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (!result)
	{
		printf("Mrd! Malloc!");
		exit(1);
	}
	temp = g_start;
	i = 0;
	while (temp)
	{
		result[i] = temp->var;
		temp = temp->next;
		i++;
	}
	return (result);
}

static void	ft_initialize_readline(void)
{
	rl_bind_key ('\t', rl_insert);
//	rl_bind_keyseq ("\\C-d", rl_insert);


}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	char	**cmd;
	char	**env;

	(void)argc;
	(void)argv;

	ft_initialize_readline();
	ft_make_env(envp);
	input = (char *)NULL;
	while (1)
	{
		if (input)
			input = (char *)NULL;
		input = readline("MRDSHLL>");
		input[ft_strlen(input)] = '\0';
		if (input && *input)
			add_history(input);
		cmd = ft_split(input, ' ');

		if (cmd[0] == NULL)
			printf("Mrd! Command not found!\n");
		else if (ft_isinn_cmd(cmd[0]))
			ft_runinn_cmd(cmd, input);
		else
		{
			env = ft_to_array();
			if (ft_abs_path(cmd, env))
				ft_run_cmd(cmd, env);
			else
				printf("Mrd! Command not found!\n");
			free(env);
			env = NULL;
		}
		ft_free_array(cmd);
	}
	ft_free_env();
	printf("A tout!\n");
	free(input);
	return (0);
}
