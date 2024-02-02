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

static int	manage_basic_redir(t_token *token)
{

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
		return (1);
	}
	next_cmd = get_next_cmd(token);
	if (!next_cmd)
		return (0); // in the real bash no next command must be work
	if (pipe(fd) < 0)
		return (1);
	update_file_descriptors(prev_cmd, prev_cmd->fd_in, fd[1]);
	update_file_descriptors(next_cmd, fd[0], next_cmd->fd_out);
}

static int	manage_heredoc(t_token *token)
{
	
}

int	formatting_redirections(t_base *base)
{
	t_token	*token;
    
    token = get_first_token(base);
    while (token)
    {
		if (is_token_redirec(token))
		{
			if (is_token_basic_redir(token))
				manage_basic_redir(token);
			if (token->id == TOKEN_PIPE)
				manage_pipe_redir(token);
			if (token->id == TOKEN_HEREDOC)
				manage_heredoc(token);
		}
		token = token->next;
    }
    return (1);
}