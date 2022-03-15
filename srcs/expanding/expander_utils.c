/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:22:42 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/13 21:06:51 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_addchar(char *dest, char c)
{
	char	*ret;

	ret = ft_calloc(ft_strlen(dest) + 3, sizeof(char));
	ft_strlcpy(ret, dest, ft_strlen(dest) + 1);
	ret[ft_strlen(dest)] = c;
	return (ret);
}

char	*ft_getvar(char *src)
{
	int		i;
	char	*ret;
	char	*swp;

	i = -1;
	ret = ft_calloc(1, sizeof(char));
	if (*src == '?')
	{
		swp = ret;
		ret = ft_addchar(ret, '?');
		free(swp);
		return (ret);
	}
	while (ft_isalnum(src[++i]) || src[i] == '_')
	{
		swp = ret;
		ret = ft_addchar(ret, src[i]);
		free(swp);
		if (!ret)
			return (NULL);
	}
	swp = ret;
	ret = ft_addchar(ret, '=');
	free(swp);
	return (ret);
}

int	ft_addvar(char **dest, char *src, char **env)
{
	int		i;
	int		varlen;
	char	*var;
	char	*swp;

	i = -1;
	var = ft_getvar(src);
	if (!var)
		return (0);
	i = 0;
	if (*var == '?')
	{
		swp = *dest;
		*dest = ft_addchar(swp, g_data->env->status + '0');
		free(swp);
		free(var);
		return (1);
	}
	while (env[i] && ft_strncmp(env[i], var, ft_strlen(var)) != 0)
		i++;
	if (env[i])
		*dest = ft_joinfree(*dest, env[i] + ft_strlen(var));
	varlen = ft_strlen(var) - 1;
	free(var);
	return (varlen);
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
