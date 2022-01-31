/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:03:02 by alemarch          #+#    #+#             */
/*   Updated: 2021/11/28 14:04:25 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		s1_len;
	int		s2_len;

	if (s1 || s2)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		ret = malloc((s1_len + s2_len + 1) * sizeof(char));
		if (!ret)
			return (NULL);
		i = 0;
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
		i = 0;
		while (s2[i])
			ret[s1_len++] = s2[i++];
		ret[s1_len] = '\0';
		return (ret);
	}
	return (NULL);
}
