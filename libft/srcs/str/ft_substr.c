/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:34:49 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/25 14:49:39 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (len--)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
