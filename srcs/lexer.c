/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:23:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/03 18:55:16 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*loadfile(char *path, int isinput)
{
	char	*ret;
	int		size;
	int		i;

	path++;
	while (*path && *path == ' ')
		path++;
	size = 0;
	if (isinput)
		while (path[size] && path[size] != ' ')
			size++;
	else
		while (path[size] && (path[size] != '|' || path[size] != '\0'))
			size++;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = path[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*loadcmd(char *cmd)
{
	char	*ret;
	int		size;
	int		i;

	size = 0;
	while (cmd[size] && cmd[size] != '>')
		size++;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = cmd[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	free_cmd(t_command *cmd)
{
	free(cmd->cmd);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	free(cmd);
}

static t_command	*parsecmd(char *cmd)
{
	int			i;
	t_command	*ret;

	i = 0;
	ret = malloc(sizeof(t_command));
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '<')
	{
		ret->infile = loadfile((cmd + i), 1);
		if (!ret->infile)
		{
			free_cmd(ret);
			return (NULL);
		}
		i += ft_strlen(ret->infile) + 2;
	}
	else
		ret->infile = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	ret->cmd = loadcmd((cmd + i));
	if (!ret->cmd)
	{
		free_cmd(ret);
		return (NULL);
	}
	i += ft_strlen(ret->cmd);
	if (cmd[i] == '>')
	{
		ret->outfile = loadfile((cmd + i), 0);
		if (!ret->outfile)
		{
			free_cmd(ret);
			return (NULL);
		}
	}
	else
		ret->outfile = 0;
	return (ret);
}

static t_command	**addcmd(t_command **cmdtable, t_command *newcmd)
{
	t_command	**ret;
	int			size;
	int			i;

	if (!cmdtable)
	{
		ret = malloc(2 * sizeof(t_command *));
		if (!ret)
			return (NULL);
		ret[0] = newcmd;
		ret[1] = NULL;
		return (ret);
	}
	size = 0;
	while (cmdtable[size])
		size++;
	ret = malloc((size + 1) * sizeof(t_command *));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < size)
		ret[i] = cmdtable[i];
	ret[i] = newcmd;
	ret[i + 1] = NULL;
	free(cmdtable);
	return (ret);
}

t_command	**ft_lexer(char *inputline)
{
	t_command	**ret;
	t_command	*newcmd;
	char		**commands;
	int			i;

	commands = ft_split(inputline, '|');
	ret = NULL;
	if (!commands)
		return (NULL);
	i = 0;
	while (commands[i])
	{
		newcmd = parsecmd(commands[i]);
		if (!newcmd)
		{
			ft_freesplit(commands);
			return (NULL);
		}
		ret = addcmd(ret, newcmd);
		i++;
	}
	return (ret);
}
