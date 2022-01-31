/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:09:08 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/19 10:34:09 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
		*(unsigned char *)(s + i++) = c;
	return (s);
}
