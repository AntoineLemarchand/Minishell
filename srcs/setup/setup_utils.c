/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:11:42 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/13 21:09:42 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_unset(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && !(name[i] == '_'))
		{
			ft_putendl_fd("unset : not a valid identifier", 2);
			return (false);
		}
	}
	return (true);
}

void	ft_unset(char **cmd, t_env *g_start)
{
	t_env	*temp;
	size_t	size;
	char	*var;
	t_env	*swap;

	if (!cmd[1])
		return ;
	if (!ft_check_unset(cmd[1]))
		return ;
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
