/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:11:00 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/01 14:15:52 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_file_redir(t_base *base, t_cmd *cmd,
		int type, char *filepath)
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

static int	manage_basic_redir(t_base *base, t_token *token)
{
	int		error;
	t_redir	*redir;
	t_cmd	*prev_cmd;
	t_cmd	*next_cmd;

	redir = get_token_class(token);
	prev_cmd = get_prev_cmd_no_skip(token);
	next_cmd = get_next_cmd_no_skip(token);
	if (prev_cmd && !next_cmd)
	{
		if (!manage_file_redir(base, prev_cmd,
			token->id, redir->filepath))
			return (-1);
		}
	else if (!prev_cmd && next_cmd)
	{
		if (!manage_file_redir(base, next_cmd,
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

static int	manage_heredoc(t_base *base, t_token *token)
{
	t_cmd	*cmd;
	int		error;
	t_redir	*redir;
	
	error = 0;
	redir = get_token_class(token);
	cmd = get_prev_cmd_no_skip(cmd);
	if (cmd == NULL)
	{
		cmd = get_next_cmd_no_skip(cmd);
		if (cmd != NULL)
			error = init_heredoc(base, redir, cmd);
		else
			return (-1); // error (no prev/next cmd)
	}	
	else
		error = init_heredoc(base, redir, cmd);
	if (error < 0)
	{
		// -1 error fork
		// -2 error heredoc
		return (-1);
	}
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
				if (!manage_basic_redir(base, token))
					return (-1);
			if (token->id == TOKEN_PIPE)
				if (!manage_pipe_redir(token))
					return (-1);
			if (token->id == TOKEN_REDIR_HDOC)
				if (!manage_heredoc(base, token))
					return (-1);
		}
		token = token->next;
    }
    return (1);
}