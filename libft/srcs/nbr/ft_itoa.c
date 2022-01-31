/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:36:41 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/24 15:04:54 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_get_nsize(int n)
{
	int	size;

	size = 0;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*ft_strrev(char *s)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (j > i)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
		j--;
	}
	return (s);
}

static void	ft_make_str(int n, char *s, int neg)
{
	int		i;

	i = 0;
	while (n)
	{
		if (neg)
			s[i++] = (-n % 10) + '0';
		else
			s[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		s[i++] = '-';
	s[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		size;
	int		neg;

	neg = 0;
	size = ft_get_nsize(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		neg++;
		size++;
	}
	ret = malloc((size + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_make_str(n, ret, neg);
	return (ft_strrev(ret));
}
