/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:42:37 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/24 14:42:40 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr;
	t_list	*curr_next;

	curr = *lst;
	while (curr)
	{
		curr_next = curr->next;
		ft_lstdelone(curr, del);
		curr = curr_next;
	}
	*lst = NULL;
}
