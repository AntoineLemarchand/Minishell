/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:20:46 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/23 10:18:49 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

unsigned long	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	dest_len;
	unsigned long	src_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen((char *)src);
	if (size > dest_len)
	{
		while (src[i] && i < (size - 1) - dest_len)
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		dest[dest_len + i] = '\0';
		return (dest_len + src_len);
	}
	else
		return (size + src_len);
}
