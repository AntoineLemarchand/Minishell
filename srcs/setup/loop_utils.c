/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:30:14 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/06 18:37:32 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_end(t_env *envcpy)
{
	ft_free_env(envcpy);
	close(0);
	close(1);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
}

void	ft_free_array(char **array)
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

void	ft_add_path(char **cmd, char **path_split)
{
	size_t	i;
	char	*bin;

	i = 0;
	while (path_split[i])
	{
		bin = ft_calloc(sizeof(char), (ft_strlen(path_split[i])
					+ ft_strlen(cmd[0]) + 2));
		if (!bin)
			break ;
		ft_strlcat(bin, path_split[i], (ft_strlen(bin) \
					+ ft_strlen(path_split[i]) + 1));
		ft_strlcat(bin, "/", (ft_strlen(bin) + 2));
		ft_strlcat(bin, cmd[0], (ft_strlen(bin) + ft_strlen(cmd[0]) + 1));
		if (access(bin, F_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = ft_strdup(bin);
			free(bin);
			break ;
		}
		free(bin);
		i++;
	}
}

void	ft_abs_path(char **cmd, t_env *g_start)
{
	char	*path;
	char	**path_split;

	if (get_env_var("PATH=", g_start))
		path = ft_strdup(&get_env_var("PATH=", g_start)[5]);
	else
		return ;
	if (cmd && cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		free(path);
		ft_add_path(cmd, path_split);
		ft_free_array(path_split);
	}
	else
	{
		free(path);
		path = NULL;
	}
}
