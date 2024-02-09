/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:11:00 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 15:36:00 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	manage_file_redir(t_cmd *cmd, int type, char *filepath)
{
	if (type == TOKEN_REDIR_IN)
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		cmd->fd_in = open_file(filepath, 0);
		if (cmd->fd_in < 0)
			return (-1);
	}
	if (type == TOKEN_REDIR_OUT)
	{
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
		cmd->fd_out = open_file(filepath, 2);
		if (cmd->fd_out < 0)
			return (-1);
	}
	if (type == TOKEN_REDIR_APP)
	{
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
		cmd->fd_out = open_file(filepath, 1);
		if (cmd->fd_out < 0)
			return (-1);
	}
	return (1);
}

static int	manage_basic_redir(t_token *token)
{
	t_redir	*redir;
	t_cmd	*prev_cmd;
	t_cmd	*next_cmd;

	redir = get_token_class(token);
	prev_cmd = get_prev_cmd_no_skip(token);
	next_cmd = get_next_cmd_no_skip(token);
	if (prev_cmd && !next_cmd)
	{
		if (!manage_file_redir(prev_cmd,
			token->id, redir->filepath))
			return (-1);
	}
	else if (!prev_cmd && next_cmd)
	{
		if (!manage_file_redir(next_cmd,
			token->id, redir->filepath))
			return (-1);
	}
	return (1);
}

static int	manage_pipe_redir(t_token *token)
{
	int		fd[2];
	t_cmd	*prev_cmd;
	t_cmd	*next_cmd;

	prev_cmd = get_prev_cmd(token);
	if (!token->prev || !prev_cmd)
	{
		ft_putstr_fd("syntax near unexpected token '|'", STDOUT_FILENO);
		return (-1);
	}
	next_cmd = get_next_cmd(token);
	if (!next_cmd)
		return (0); // in the real bash no next command must be work with a separate prompt
	if (pipe(fd) < 0)
		return (-1);
	prev_cmd->fd_out = fd[1];
	next_cmd->fd_in = fd[0];
	return (1);
}

static int	manage_heredoc(t_base *base, t_token *token) // Manage if any command not found
{
	t_cmd	*cmd;
	t_redir	*redir;

	redir = get_token_class(token);
	cmd = get_prev_cmd_no_skip(cmd);
	if (cmd == NULL)
	{
		cmd = get_next_cmd_no_skip(cmd);
		if (cmd != NULL)
		{
			if (init_heredoc(base, redir, cmd) == -2)
				return (-2);
		}	
		else if (init_heredoc(base, redir,
            (t_cmd *){TOKEN_CMD, 0, NULL, NULL, -1, -1, NULL, NULL}) == -2)
			return (-2);
	}
	else
		if (init_heredoc(base, redir, cmd) == -2)
			return (-2);
	return (1);
}

int	format_redirections(t_base *base)
{
	t_token	*token;

	token = get_first_token(base);
	while (token)
	{
		if (is_token_redirec(token))
		{
			if (is_token_basic_redir(token))
				if (!manage_basic_redir(token))
					base->exit_status = EXIT_FAILURE;
			if (token->id == TOKEN_PIPE)
				if (!manage_pipe_redir(token))
					return (-1); // Change to remove
			if (token->id == TOKEN_REDIR_HDOC)
				if (manage_heredoc(base, token) == 2)
					return (-2);
		}
		token = token->next;
	}
	return (1);
}
