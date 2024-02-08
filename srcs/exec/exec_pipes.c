/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:53 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/07 16:02:17 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_pipes(t_base *base)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		pipe;
	int		fd[2];

	pipe = 0;
	cmd = get_next_cmd(get_first_token(base));
	while (cmd != NULL)
	{
		if (is_cmd_builtin(cmd))
			return (1); // exec_builtin(); // update exit code
		// check export
	}
	pid = fork();
	if (pid == 0) // Child
		return (1); // exec_child();
	else // Parent
	{

	}
	return (1);
}