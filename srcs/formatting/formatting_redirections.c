/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:11:00 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 15:56:28 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_files(t_cmd *cmd, int type, char *filepath)
{
	if (type == TOKEN_REDIR_IN)
	{
		if (manage_in(cmd, filepath) == -1)
		{
			perror(filepath);
			return (-1);
		}
	}
	else if (type == TOKEN_REDIR_OUT)
	{
		if (manage_out(cmd, filepath) == -1)
		{
			perror(filepath);
			return (-1);
		}
	}
	else if (type == TOKEN_REDIR_APP)
	{
		if (manage_append(cmd, filepath) == -1)
		{
			perror(filepath);
			return (-1);
		}
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
		if (manage_files(prev_cmd,
				token->id, redir->filepath) == -1)
			return (-3);
	}
	else if (!prev_cmd && next_cmd)
	{
		if (manage_files(next_cmd,
				token->id, redir->filepath) == -1)
			return (-3);
	}
	return (1);
}

static int	manage_pipe(t_base *base, t_token *token)
{
	if (!token->prev)
	{
		ft_putstr_fd("syntax near unexpected token '|'\n", STDERR_FILENO);
		base->exit_status = 258;
		return (-2);
	}
	else if (!token->next)
	{
		if (prompt_cmd(base) == -1)
			return (-2);
		if (errors_lexer(base) == 1)
			return (-2);
	}
	if (pipe_redir(token) == -1)
		return (-1);
	return (1);
}

static int	manage_heredoc(t_base *base, t_token *token)
{
	t_cmd	*cmd;
	t_redir	*redir;

	redir = get_token_class(token);
	cmd = get_prev_cmd_no_skip(token);
	if (cmd == NULL)
	{
		cmd = get_next_cmd_no_skip(token);
		if (cmd != NULL)
		{
			if (init_heredoc(base, redir, cmd) == -2)
				return (-2);
		}	
		else if (init_heredoc(base, redir, NULL) == -2)
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
		if (is_token_basic_redir(token))
		{
			if (manage_basic_redir(token) < 0)
				return (-3);
		}
		else if (is_token_pipe(token))
		{
			if (manage_pipe(base, token) == -2)
				return (-2);
		}
		else if (token->id == TOKEN_REDIR_HDOC)
		{
			if (manage_heredoc(base, token) == -2)
				return (-2);
		}
		token = token->next;
	}
	return (1);
}
