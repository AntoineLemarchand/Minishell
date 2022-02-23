/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:42:56 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/23 17:12:38 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_addchar(char *dest, char c)
{
	char	*ret;

	ret = ft_calloc(ft_strlen(dest) + 2, sizeof(char));
	ft_strlcpy(ret, dest, ft_strlen(dest) + 1);
	ret[ft_strlen(dest)] = c;
	return (ret);
}

static char	*ft_addvar(char *dest, char *src, char **env)
{
	int		i;
	char	*var;
	char	*swp;

	i = -1;
	var = ft_calloc(1, sizeof(char));
	while (ft_isalnum(src[++i]))
	{
		swp = var;
		var = ft_addchar(var, src[i]);
		free(swp);
		if (!var)
			return (NULL);
	}
	swp = var;
	var = ft_strjoin(var, "=\0");
	free(swp);
	if (!var)
		return (NULL);
	i = 0;
	while (env[i] && !ft_strncmp(env[i], var, ft_strlen(var)))
		i++;
	if (env[i])
	{
		swp = dest;
		dest = ft_strjoin(var, env[i] + ft_strlen(var));
		free(swp);
		if (!dest)
			free(var);
		if (!dest)
			return (NULL);
	}
	return (dest);
}

static char	*ft_expandval(char *s, char **env)
{
	int		i;
	char	*ret;
	char	*swp;
	
	i = 0;
	ret = ft_calloc(1, sizeof(char));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			ret = ft_addvar(ret, s + i + 1, env);
			i = ft_strlen(ret);
		}
		else
		{
			swp = ret;
			ret = ft_addchar(ret, s[i]);
			free(swp);
		}
		if (!ret)
			return (NULL);
		i++;
	}
	return (ret);
}

int	ft_expand(t_tok **toks, char **env)
{
	int		i;
	char	*swp;

	i = 0;
	while (toks[i])
	{
		if (toks[i]->type == DOUBLEQUOTE || toks[i]->type == LITERAL)
		{
			swp = toks[i]->val;
			toks[i]->val = ft_expandval(toks[i]->val, env);
			free(swp);
			if (!toks[i]->val)
				return (1);
		}
		i++;
	}
	return (0);
}
