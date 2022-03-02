/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:09:43 by imarushe          #+#    #+#             */
/*   Updated: 2022/03/02 13:22:13 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *var)
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

void	ft_add_env(char *var)
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

void	ft_add_var_list(char **var_list)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (var_list[i])
			ft_add_var(var_list[i]);
		i++;
	}
}

void	ft_add_var(char *var)
{
	char			*result;

	result = NULL;
	if (!ft_strncmp(var, "PATH=", 5))
		result = ft_strdup(var);
	else if (!ft_strncmp(var, "OLDPWD=", 7))
		result = ft_strdup("OLDPWD=");
	else if (!ft_strncmp(var, "PWD=", 4))
		result = built_in_pwd();
	if (!result)
		return ;
	ft_add_env(result);
}

void	ft_make_env(char **envp)
{
	char	*var_list[4];
	int		i;

	i = 0;
	var_list[0] = "PATH";
	var_list[1] = "OLDPWD";
	var_list[2] = "PWD";
	var_list[3] = NULL;
	while (envp[i] != NULL)
	{
		ft_add_env(ft_strdup(envp[i]));
		if (!ft_strncmp(envp[i], "PATH", 4))
			var_list[0] = NULL;
		else if (!ft_strncmp(envp[i], "OLDPWD", 6))
			var_list[1] = NULL;
		else if (!ft_strncmp(envp[i], "PWD", 3))
			var_list[2] = NULL;
		i++;
	}
	ft_add_var_list(var_list);
}
