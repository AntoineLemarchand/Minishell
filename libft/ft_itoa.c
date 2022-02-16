/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:36:41 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/16 17:23:23 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_len(long n)
{
	int		len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_write(long n, int len, char *str)
{
	int		start;

	start = 0;
	str[len] = '\0';
	len--;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		start = 1;
	}
	while (len >= start)
	{
		str[len] = n % 10 + 48;
		n /= 10;
		len--;
	}
}

char	*ft_itoa(long n)
{
	int		count_char;
	char	*str;

	count_char = ft_len(n);
	str = (char *)malloc(sizeof(char) * count_char + 1);
	if (str == NULL)
		return (NULL);
	ft_write(n, count_char, str);
	return (str);
}
