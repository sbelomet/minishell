/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_redirections_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:44:30 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 16:16:41 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_in(t_cmd *cmd, char *filepath)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	cmd->fd_in = open(filepath, O_RDONLY, 0644);
	if (cmd->fd_in < 0)
		return (-1);
	return (1);
}

int	manage_out(t_cmd *cmd, char *filepath)
{
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	cmd->fd_out = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		return (-1);
	return (1);
}

int	manage_append(t_cmd *cmd, char *filepath)
{
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	cmd->fd_out = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_out < 0)
		return (-1);
	return (1);
}

int	pipe_redir(t_token *token)
{
	int		fd[2];
	t_cmd	*prev_cmd;
	t_cmd	*next_cmd;

	prev_cmd = get_prev_cmd(token);
	next_cmd = get_next_cmd(token);
	if (prev_cmd && next_cmd)
	{
		if (pipe(fd) < 0)
			return (-1);
		prev_cmd->fd_out = fd[1];
		next_cmd->fd_in = fd[0];
	}
	return (1);
}
