/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:23:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/02/04 13:06:03 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_command *cmd)
{
	if (cmd)
	{
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd->cmd);
		free(cmd);
	}
}

static t_command	*parsecmd(char *cmd)
{
	int			i;
	int			end;
	t_command	*ret;

	i = 0;
	ret = malloc(sizeof(t_command));
	if (load_io(cmd, ret) || load_cmd(cmd, ret))
	{
		free_cmd(ret);
		return (NULL);
	}
	if (ret->outfile)
	{
		end = ft_strlen(cmd);
		while (cmd[end] != '>')
			end--;
		if (end - 1 >= 0 && cmd[end - 1] == '>')
			ret->appendmode = 1;
		else
			ret->appendmode = 0;
	}
	else
		ret->appendmode = 0;
	return (ret);
}

static t_command	**addcmd(t_command **cmdtable, t_command *newcmd)
{
	t_command	**ret;
	int			size;
	int			i;

	if (!cmdtable)
		ret = malloc(2 * sizeof(t_command *));
	size = 0;
	while (cmdtable && cmdtable[size])
		size++;
	if (cmdtable)
		ret = malloc((size + 2) * sizeof(t_command *));
	if (!ret)
		return (NULL);
	i = 0;
	while (cmdtable && cmdtable[i])
	{
		ret[i] = cmdtable[i];
		i++;
	}
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
	ft_freesplit(commands);
	return (ret);
}
