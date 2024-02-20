/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_redirections_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:44:30 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/19 14:46:30 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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