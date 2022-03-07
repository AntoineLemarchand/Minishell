/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:42:56 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/07 19:28:21 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_addchar(char *dest, char c)
{
	char	*ret;

	ret = ft_calloc(ft_strlen(dest) + 2, sizeof(char));
	ft_strlcpy(ret, dest, ft_strlen(dest) + 1);
	ret[ft_strlen(dest)] = c;
	return (ret);
}

static char	*ft_getvar(char *src)
{
	int		i;
	char	*ret;
	char	*swp;

	i = -1;
	ret = ft_calloc(1, sizeof(char));
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

static int	ft_addvar(char **dest, char *src, char **env)
{
	int		i;
	int		varlen;
	char	*var;

	i = -1;
	var = ft_getvar(src);
	if (!var)
		return (0);
	i = 0;
	while (env[i] && ft_strncmp(env[i], var, ft_strlen(var)) != 0)
		i++;
	if (env[i])
		*dest = ft_joinfree(*dest, env[i] + ft_strlen(var));
	varlen = ft_strlen(var) - 1;
	free(var);
	return (varlen);
}

char	*ft_expandval(char *s, char **env)
{
	int		i;
	char	*ret;
	char	*swp;

	ret = ft_calloc(1, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] != '$' || (s[i] == '$' && s[i + 1] == '?'))
		{
			swp = ret;
			ret = ft_addchar(ret, s[i++]);
			free(swp);
		}
		else if (++i)
			i += ft_addvar(&ret, s + i, env);
		if (!ret)
			return (NULL);
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
