/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:10:57 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/24 15:20:40 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*to_add;

	if (!lst || !f)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		to_add = ft_lstnew(f(lst->content));
		if (!to_add)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, to_add);
		to_add = to_add->next;
		lst = lst->next;
	}
	return (ret);
}
