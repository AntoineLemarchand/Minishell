/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:57:38 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/29 09:33:45 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, char c)
{
	int	i;

	i = (int)ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
