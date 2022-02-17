/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 22:54:03 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/16 22:54:13 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_env(void)
{
	size_t	i;

	i = 0;
	g_status = 0;
	while (g_envs[i])
	{
		if (ft_strchr(g_envs[i], '='))
		{
			ft_putstr_fd(g_envs[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (1);
}
