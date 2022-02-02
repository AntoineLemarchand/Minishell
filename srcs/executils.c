/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:45:03 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/02 10:53:03 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_joincommand(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		s1_len;
	int		s2_len;

	if (s1 && s2)
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
		while (s2[i] && s2[i] != ' ')
			ret[s1_len++] = s2[i++];
		ret[s1_len] = '\0';
		return (ret);
	}
	return (NULL);
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
