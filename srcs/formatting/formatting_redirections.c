/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:11:00 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/15 16:06:28 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = open_file(filepath, 2);
		if (cmd->fd_out < 0)
			return (-1);
	}
	if (type == TOKEN_REDIR_APP)
	{
		if (cmd->fd_out != 1)
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

    printf("pipe token: %d\n", token->prev->id);
	if (!token->prev)
	{
		ft_putstr_fd("syntax near unexpected token '|'\n", STDERR_FILENO);
		return (-1);
	}
	if (!token->next)
		// open prompt and lexer to add new token at the end of the stack
	prev_cmd = get_prev_cmd(token);
	next_cmd = get_next_cmd(token);
	if (pipe(fd) < 0)
		return (-1);
	dup2(prev_cmd->fd_in, fd[1]);
	prev_cmd->fd_out = fd[1];
	next_cmd->fd_in = fd[0];
	wait(NULL);
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
		printf("id token: %d\n", token->id);
		if (is_token_redirec(token) || token->id == TOKEN_PIPE)
		{
			if (is_token_basic_redir(token))
			{
				printf("basic redir\n");
				if (manage_basic_redir(token) == -1)
					base->exit_status = EXIT_FAILURE;
			}
			else if (is_token_pipe(token))
			{
				printf("pipe\n");
				if (!manage_pipe_redir(token))
					return (-1); // Change to remove
			}
			else if (token->id == TOKEN_REDIR_HDOC)
			{
				if (manage_heredoc(base, token) == 2)
					return (-2);
			}
		}
		token = token->next;
	}
	printf("DEBBUG END FORMATTING\n");
	return (1);
}
