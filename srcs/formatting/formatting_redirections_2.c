/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_redirections_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:55:56 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/05 16:25:43 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_infile_redir(t_base *base, t_cmd *cmd,
		t_token *token, char *filepath)
{
	if (token == TOKEN_REDIR_IN)
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		cmd->fd_in = open_file(filepath, 0);
		if (cmd->fd_in < 0)
			return (-1);
	}
}

int	manage_outfile_redir(t_base *base, t_cmd *cmd,
		t_token *token, char *filepath)
{
	if (token == TOKEN_REDIR_OUT)
	{
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
		cmd->fd_out = open_file(filepath, 2);
		if (cmd->fd_out < 0)
			return (-1);
	}
}

int	manage_outfile_redir(t_base *base, t_cmd *cmd,
		t_token *token, char *filepath)
{
	if (token == TOKEN_REDIR_APP)
	{
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
		cmd->fd_out = open_file(filepath, 1);
		if (cmd->fd_out < 0)
			return (-1);
	}
}

int	manage_file_redir(t_base *base, t_cmd *cmd,
		t_token *token, char *filepath)
{
	// check what basic redir is
}