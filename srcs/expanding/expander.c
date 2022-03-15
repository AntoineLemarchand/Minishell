/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:42:56 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/15 10:28:29 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shouldexpand(char *s, int i)
{
	int	j;
	int	ret;

	j = i;
	ret = 0;
	while (j >= 0)
	{
		if (s[j] == '"')
			ret = 0;
		else if (s[j] == '\'')
			ret = 1;
		j--;
	}
	return (ret);
}

char	*ft_expandval(char *s, char **env, int i)
{
	char	*ret;
	char	*swp;

	ret = ft_calloc(1, sizeof(char));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		if (shouldexpand(s, i) || s[i] != '$' || (s[i] == '$'
				&& (!s[i + 1] || (ft_isspace(s[i + 1]) && !ft_isalnum(s[i + 1])
						&& s[i + 1] != '_' && s[i + 1] != '?'))))
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

int	process_char(char *val, char **ret, int i)
{
	char	*swp;
	char	control;

	if (val[i] == '\'' || val[i] == '"')
	{
		control = val[i++];
		while (val[i] && val[i] != control)
		{
			swp = *ret;
			*ret = ft_addchar(*ret, val[i++]);
			free(swp);
			if (!*ret)
				return (0);
		}
	}
	else
	{
		swp = *ret;
		*ret = ft_addchar(*ret, val[i]);
		free(swp);
		if (!*ret)
			return (0);
	}
	return (i);
}

char	*ft_cleanquotes(char *val)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc(1, sizeof(char));
	if (!ret)
		return (NULL);
	while (val && val[i])
	{
		i = process_char(val, &ret, i);
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
		if (!i
			|| !(toks[i - 1]->type == INREDIR && ft_strlen(toks[i]->val) == 2))
		{
			swp = toks[i]->val;
			toks[i]->val = ft_expandval(toks[i]->val, env, 0);
			free(swp);
			if (!toks[i]->val)
				return (1);
		}
		swp = toks[i]->val;
		toks[i]->val = ft_cleanquotes(toks[i]->val);
		free(swp);
		if (!toks[i]->val)
			return (1);
		i++;
	}
	return (0);
}
