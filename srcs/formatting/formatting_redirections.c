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

static void	update_file_descriptors(t_cmd *cmd, int in, int out)
{
	cmd->fd_in = in;
	cmd->fd_out = out;
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
	{} //
	else if (!prev_cmd && next_cmd)
	{} //
	if (!manage_infile_redir)
		return (-1);
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
	update_file_descriptors(prev_cmd, prev_cmd->fd_in, fd[1]);
	update_file_descriptors(next_cmd, fd[0], next_cmd->fd_out);
}

static int	manage_heredoc(t_base *base, t_token *token)
{
	t_cmd	*cmd;
	int		error;
	t_redir	*redir;
	
	error = 0;
	redir = get_token_class(token);
	cmd = get_prev_cmd(cmd);
	if (cmd == NULL)
	{
		cmd = get_next_cmd(cmd);
		if (cmd != NULL)
			error = init_heredoc(base, redir, cmd);
		else
			return (-1); // printf error (no prev/next cmd)
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
				manage_basic_redir(base, token); // add error handling
			if (token->id == TOKEN_PIPE)
				manage_pipe_redir(token); // add error handling
			if (token->id == TOKEN_REDIR_HDOC)
				manage_heredoc(base, token); // add error handling
		}
		token = token->next;
    }
    return (1);
}