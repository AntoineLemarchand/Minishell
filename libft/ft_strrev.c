/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:37:21 by imarushe          #+#    #+#             */
/*   Updated: 2022/02/16 14:37:27 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*rev;
	int		len;

	len = ft_strlen(str);
	rev = (char *)malloc(sizeof(char *) * (len + 1));
	while (len--)
		rev[len] = *(str++);
	return (rev);
}
