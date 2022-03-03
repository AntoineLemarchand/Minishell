/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:11:42 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/03 16:22:55 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **cmd, t_env *g_start)
{
	int		i;
	char	*str;
	char	*name;

	i = 0;
	name = NULL;
	while (cmd[1] && cmd[1][i] != '=')
		i++;
	name = ft_calloc(sizeof(char), i + 2);
	if (!name)
		return ;
	ft_strlcpy(name, cmd[1], i + 2);
	if (get_env_var(name, g_start))
	{
		str = ft_strrchr(get_env_var(name, g_start), '=') + 1;
		str = &str[-ft_strlen(name)];
		ft_strlcpy(str, cmd[1], ft_strlen(cmd[1]) + 1);
	}
	else
		ft_add_env(ft_strdup(cmd[1]), g_start);
	free(name);
}
void	ft_unset(char **cmd, t_env *g_start)
{
	t_env	*temp;
	size_t	size;
	char	*var;
	t_env	*swap;

	var = ft_strdup(cmd[1]);
	temp = g_start;
	size = ft_strlen(var);
	while (temp && temp->next)
	{
		if (!ft_strncmp(var, temp->next->var, size))
		{
			swap = temp->next;
			temp->next = temp->next->next;
			free(swap->var);
			free(swap);
		}
		temp = temp->next;
	}
	free(var);
	return ;
}

char	**ft_to_array(t_env *g_start)
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
	result = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!result)
		return (NULL);
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

void	ft_free_env(t_env *envcpy)
{
	t_env	*i;
	t_env	*temp;

	i = envcpy;
	while (i)
	{
		temp = i;
		i = i->next;
		free(temp->var);
		temp->var = NULL;
		free(temp);
		temp = NULL;
	}
	free(i);
}

void	ft_change_status(char **cmd, t_env *g_start)
{
	int		i;
	char	*temp;

	i = 1;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "$?", 2))
		{
			free(cmd[i]);
			temp = ft_itoa(g_start->status);
			cmd[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}
