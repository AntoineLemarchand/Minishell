/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:52:55 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/15 11:20:01 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_export_name(char **cmd)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (cmd[1] && cmd[1][i] && cmd[1][i] != '=')
		i++;
	if (!cmd[1][i])
		return (NULL);
	if (cmd[1][i - 1] == 43)
	{
		name = ft_calloc(sizeof(char), ft_strlen(cmd[1]));
		if (!name)
			return (NULL);
		ft_strlcpy(name, cmd[1], i);
	}
	else
	{
		name = ft_calloc(sizeof(char), ft_strlen(cmd[1]) + 1);
		if (!name)
			return (NULL);
		ft_strlcpy(name, cmd[1], i + 1);
	}
	return (name);
}

char	*ft_return_plus(int i, char *swap, char **cmd, t_env *g_start)
{
	char	*str;
	char	**temp;
	char	*name;

	temp = malloc(sizeof(char *) * 2);
	if (!temp)
		return (NULL);
	temp[0] = NULL;
	str = malloc(sizeof(char) * ft_strlen(swap) + 1);
	if (!str)
		return (NULL);
	name = get_env_var(swap, g_start);
	free(swap);
	name = ft_strjoin(name, &cmd[1][i + 1]);
	ft_strlcpy(str, cmd[1], i);
	temp[1] = ft_strdup(str);
	ft_unset(temp, g_start);
	free(str);
	free(temp[1]);
	free(temp);
	return (name);
}

char	*ft_export_exist(int i, char *swap, char **cmd, t_env *g_start)
{
	char	**temp;

	if (cmd[1][i - 1] == 43)
		return (ft_return_plus(i, swap, cmd, g_start));
	else
	{
		temp = malloc(sizeof(char *) * 2);
		if (!temp)
			return (NULL);
		temp[0] = NULL;
		temp[1] = ft_strdup(swap);
		ft_unset(temp, g_start);
		ft_strlcat(swap, &cmd[1][i], ft_strlen(cmd[1]) + 1);
		free(temp[1]);
		free(temp);
		return (swap);
	}
}

bool	ft_check_name(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && !(name[i] == '_'))
		{
			ft_putendl_fd("export : not a valid identifier", 2);
			free(name);
			return (false);
		}
	}
	return (true);
}

void	ft_export(char **cmd, t_env *g_start)
{
	int		i;
	char	*name;

	i = 0;
	if (!cmd[1])
		return ;
	while (cmd[1] && cmd[1][i] && cmd[1][i] != '=')
		i++;
	name = ft_export_name(cmd);
	if (!ft_check_name(name))
		return ;
	if (get_env_var(name, g_start))
	{
		name = ft_export_exist(i, name, cmd, g_start);
	}
	else
		ft_strlcat(name, &cmd[1][i], ft_strlen(cmd[1]) + 1);
	ft_add_env(name, g_start);
	free(name);
}
