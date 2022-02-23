/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:30:18 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/23 17:05:39 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_quotes(char *input)
{
	int		i;
	char	control;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			control = input[i];
			while (input[i] && input[i] != control)
				i++;
			if (!input[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_pipe(char *input)
{
	int		i;

	i = 0;
	while (input[i] == ' ' || (input[i] >= '\t' && input[i] <= '\r'))
		i++;
	if (input[i] == '|')
		return (1);
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i]
				&& (input[i] == ' ' || (input[i] >= '\t' && input[i] <= '\r')))
				i++;
			if (!input[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_input(char *input)
{
	return (check_quotes(input) || check_pipe(input));
}
