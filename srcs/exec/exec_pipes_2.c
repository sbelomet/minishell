/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:18:54 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 15:02:00 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	closing_all_fd(t_base *base)
{
	t_cmds	*cmds;

	cmds = base->cmds;
	while (cmds)
	{
		if (cmds->cmd->fd_in != 0)
			close(cmds->cmd->fd_in);
		if (cmds->cmd->fd_out != 1)
			close(cmds->cmd->fd_out);
		cmds = cmds->next;
	}
}

int	switching_in_out(t_base *base, t_cmd *cmd)
{
	if (cmd->fd_in != 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (error_manager(base, 1, NULL, 0));
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (error_manager(base, 1, NULL, 0));
		close(cmd->fd_out);
	}
	return (0);
}
