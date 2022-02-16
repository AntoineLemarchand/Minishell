/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip_extra_spaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:25:54 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/16 14:33:24 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_without_extra_spaces(char *str)
{
	size_t		i;
	size_t		len;
	char		found_space;

	len = ft_strlen(str);
	if (str && (len) > 0)
		while ((len - 1) > 0 && str[len - 1] && ft_isspace(str[len - 1]))
			len--;
	str[len] = '\0';
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	len -= i;
	i--;
	found_space = 0;
	while (str[++i])
	{
		if (ft_isspace(str[i]) && !found_space)
			found_space = 1;
		else if (ft_isspace(str[i]))
			len--;
		else
			found_space = 0;
	}
	return (len);
}

void	copy(char **new, char *str, size_t i)
{
	size_t	j;
	size_t	k;

	k = 0;
	j = 0;
	while (str[i])
	{
		if ((ft_isspace(str[i]) && !k))
		{
			k = 1;
			(*new)[j++] = str[i];
		}
		else if (!ft_isspace(str[i]))
		{
			k = 0;
			(*new)[j++] = str[i];
		}
		i++;
	}
	(*new)[j] = '\0';
}

void	add_space_after(char *tmp, char *whole_cmd, int v, char **new)
{
	int	i;
	int	j;

	j = ft_strlen(*new);
	i = ft_strlen(tmp) - 1;
	if (!tmp || i < 0)
		return ;
	if (tmp[i] == ' ' && follow_env(v, whole_cmd) && whole_cmd[v] == '$')
		return ;
	if (tmp[i] == ' ' && (whole_cmd[v] == '"' || whole_cmd[v] == '\''
			|| whole_cmd[v] == '/' || whole_cmd[v] == '@'
			|| whole_cmd[v] == ',' || whole_cmd[v] == '$'
			|| whole_cmd[v] == '[' || whole_cmd[v] == ']'
			|| whole_cmd[v] == '\\'))
	{
		(*new)[j] = ' ';
		(*new)[j + 1] = '\0';
	}
}

static char	*add(char *tmp, char *whole_cmd, int v, char *new)
{
	if (add_space_before(tmp, whole_cmd, v, &new) == -1)
	{
		if (tmp)
			free(tmp);
		return (new);
	}
	add_space_after(tmp, whole_cmd, v, &new);
	if (tmp)
		free(tmp);
	return (new);
}

char	*ft_strip_extra_spaces(char *str, char *whole_cmd, int v)
{
	char	*new;
	char	*tmp;
	size_t	i;
	size_t	len;

	tmp = ft_strdup(str);
	len = len_without_extra_spaces(str);
	new = (char *)malloc(sizeof(char) * (len + 3));
	if (!new)
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	i = ft_strlen(str);
	if (str && i > 0)
		while ((i - 1) > 0 && str[i - 1] && ft_isspace(str[i - 1]))
			i--;
	str[i] = '\0';
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	copy(&new, str, i);
	free(str);
	return (add(tmp, whole_cmd, v, new));
}
