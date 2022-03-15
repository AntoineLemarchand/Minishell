/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:29:08 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/10 17:08:40 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_initialize_readline(t_env *envcpy)
{
	struct termios	tp;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	if (tcgetattr(0, &tp) == -1)
		ft_putendl_fd("minishell: could not access attributes", 2);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &tp) == -1)
		ft_putendl_fd("minishell: could not access attributes", 2);
	rl_bind_key ('\t', rl_insert);
	return (envcpy);
}

static t_env	*init_basic(t_env *envcpy)
{
	envcpy->next = NULL;
	envcpy->status = 0;
	envcpy->exit = -1;
	envcpy->fdin = dup(0);
	if (!envcpy->fdin)
		return (NULL);
	return (envcpy);
}

t_env	*init_fullenv(char **env, t_env *envcpy)
{
	envcpy->var = ft_calloc(1, sizeof(char));
	if (!envcpy->var)
	{
		free(envcpy);
		return (NULL);
	}
	envcpy = init_basic(envcpy);
	if (!envcpy)
		return (NULL);
	envcpy = ft_make_env(env, envcpy);
	if (!envcpy)
		return (NULL);
	envcpy = ft_initialize_readline(envcpy);
	if (!envcpy)
		return (NULL);
	return (envcpy);
}

t_env	*init_emptyenv(t_env *envcpy)
{
	char	cwd[1024];
	char	*pwd;
	char	*oldpwd;
	char	*path;

	getcwd(cwd, sizeof(cwd));
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (NULL);
	envcpy->var = pwd;
	envcpy = init_basic(envcpy);
	if (!envcpy->fdin)
		return (NULL);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (NULL);
	ft_add_env(oldpwd, envcpy);
	free(oldpwd);
	path = ft_strdup("PATH=");
	if (!path)
		return (NULL);
	ft_add_env(path, envcpy);
	free(path);
	return (envcpy);
}
