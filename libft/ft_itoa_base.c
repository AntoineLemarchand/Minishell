/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:44:32 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/16 13:59:20 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(long n, int base)
{
	int	size;

	size = 0;
	while (n > 0)
	{
		n /= base;
		size++;
	}
	return (size);
}

char	*ft_itoa_base(long n, int base, int big)
{
	char	*str;
	int		len;
	char	letter;

	if (!n)
		return (ft_strdup("0"));
	if (big)
		letter = 'A';
	else
		letter = 'a';
	len = ft_size(n, base);
	str = (char *)malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (n)
	{
		if (n % base < 0xA)
			str[len] = n % base + 48;
		else
			str[len] = letter + n % base - 0xA;
		n /= base;
		len--;
	}
	return (str);
}
