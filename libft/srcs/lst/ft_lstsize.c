/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:27:13 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/21 21:19:35 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;

	count = 0;
	if (!lst)
		return (0);
	else
		count++;
	while (lst->next)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
