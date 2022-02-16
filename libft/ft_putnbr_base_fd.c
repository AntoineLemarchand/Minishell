/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:13:35 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/16 14:15:27 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(size_t n, int base, int fd)
{
	size_t	digit;

	digit = n % base;
	n /= base;
	if (n)
		ft_putnbr_base_fd(n, base, fd);
	if (digit < 0xA)
		digit += 48;
	else
		digit += 'a' - 0xA;
	ft_putchar_fd(digit, fd);
}
