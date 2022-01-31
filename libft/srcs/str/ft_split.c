/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:23:37 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/25 15:33:23 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] != c)
		count++;
	i++;
	while (s[i - 1] && s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

static char	*ft_worddup(char const *s, char c)
{
	char	*ret;
	int		wordlen;
	int		i;

	i = 0;
	wordlen = 0;
	while (s[wordlen] && s[wordlen] != c)
		wordlen++;
	ret = malloc((wordlen + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (s[i] != '\0' && i < wordlen)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static void	ft_free_split(char **split, int n)
{
	int	i;

	i = 0;
	if (n > 0)
		n--;
	while (i < n)
		free(split[i++]);
	free(split);
	split = NULL;
}

static int	ft_fill_split(char const *s, char c, char **splitted, int size)
{
	int	i;

	i = 0;
	while (*s && i < size)
	{
		if ((*s == c) || i == 0)
		{
			while (*s == c)
				s++;
			if (*s && i < size)
			{
				splitted[i] = ft_worddup(s, c);
				if (!splitted[i++])
				{
					ft_free_split(splitted, i);
					return (1);
				}
			}
		}
		s++;
	}
	splitted[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		size;

	if (!s || !s[0])
	{
		ret = ft_calloc(1, sizeof(char *));
		return (ret);
	}
	size = ft_count_words(s, c);
	ret = malloc((size + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	if (ft_fill_split(s, c, ret, size))
		return (NULL);
	return (ret);
}
