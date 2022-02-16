/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:38:48 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/24 11:40:49 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;
	int		begin;
	int		end;

	begin = 0;
	while (ft_is_in_set(s1[begin], set))
		begin++;
	if (!s1 || begin == (int)ft_strlen((char *)s1))
		return (ft_strdup(""));
	else if (!set)
		return (ft_strdup((char *)s1));
	end = ft_strlen((char *)s1) - 1;
	while (ft_is_in_set(s1[end], set))
		end--;
	ret = malloc((end - begin + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[begin] && begin <= end)
		ret[i++] = s1[begin++];
	ret[i] = '\0';
	return (ret);
}
