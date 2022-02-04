/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:27:22 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/04 11:32:18 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmdstart(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '<')
		return (0);
	i++;
	while (line[i] && line [i] == ' ')
		i++;
	while (line[i] && line [i] != ' ')
		i++;
	while (line[i] && line [i] == ' ')
		i++;
	return (i);
}

static int	get_cmdend(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i > 0 && line[i] != '>')
		i--;
	if (i == 0)
		return (ft_strlen(line));
	i--;
	while (i > 0 && line [i] == ' ')
		i--;
	return (i);
}

int	load_cmd(char *line, t_command *cmd)
{
	char	*ret;
	int		start;
	int		end;
	int		i;

	start = get_cmdstart(line);
	end = get_cmdend(line);
	if (start == end)
	{
		cmd->cmd = NULL;
		return (0);
	}
	ret = malloc(end - start + 1);
	if (!ret)
		return (1);
	i = 0;
	while (start + i < end)
	{
		ret[i] = line[start + i];
		i++;
	}
	ret[end] = '\0';
	cmd->cmd = ret;
	return (0);
}
