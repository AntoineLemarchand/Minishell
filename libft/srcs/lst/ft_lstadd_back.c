/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:26:03 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/24 12:47:24 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*end;

	if (!new)
		return ;
	if (*alst)
	{
		end = ft_lstlast(*alst);
		end->next = new;
	}
	else
		*alst = new;
}
