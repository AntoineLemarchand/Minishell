/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:53:07 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/31 11:49:33 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putecho(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_echo(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	if (!ft_strncmp(av[i], "-n\0", 3))
		i++;
	while (av[i])
	{
		ft_putecho(av[i++]);
		if (av[i])
			write(1, " ", 1);
	}
	if (ft_strncmp(av[1], "-n\0", 3) != 0)
		write(1, "\n", 1);
	return ;
}
