/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:20:31 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/29 09:33:35 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned long	s_len;
	unsigned long	i;
	char			*ret;

	i = 0;
	s_len = 0;
	while (s[s_len])
		s_len++;
	ret = malloc((s_len + 1) * sizeof(char));
	if (!ret || !s || !f)
		return (NULL);
	while (s[i] && i < s_len)
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
