/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:35:12 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/04 13:04:04 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_word(char *str)
{
	char	control;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	control = str[i];
	if (str[i] == '\'' || str[i] == '\"')
		while (str[i] != control)
			i++;
	else
		while (str[i] && str[i] != '\0' && str[i] != '|' && str[i] != ' ')
			i++;
	ret = malloc(i + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static char	*load_infile(char *line)
{
	int		i;
	char	*ret;

	i = 0;
	while (line[i] && line [i] != '<')
		i++;
	if (!line[i])
		return (NULL);
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	ret = dup_word((line + i));
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*load_outfile(char *line)
{
	int		i;
	char	*ret;

	i = ft_strlen(line) - 1;
	while (i && line [i] != '>')
		i--;
	if (line[i] != '>')
		return (NULL);
	i++;
	while (line[i] == ' ')
		i++;
	ret = dup_word((line + i));
	if (!ret)
		return (NULL);
	return (ret);
}

int	load_io(char *line, t_command *cmd)
{
	cmd->infile = load_infile(line);
	cmd->outfile = load_outfile(line);
	return (0);
}
