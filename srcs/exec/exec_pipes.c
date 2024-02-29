/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:53 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 15:10:07 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launching_command(t_base *base, t_cmd *cmd)
{
	if (cmd->path)
	{
		if (execve(cmd->path, get_args_tab(cmd->first_arg, cmd->path),
				base->env) == -1)
		{
			base->exit_status = 127;
			exit(127);
		}
	}
}

void	child_process(t_base *base, t_cmd *cmd)
{
	int	pid;

	signal(SIGINT, ft_ctrl_c2);
	signal(SIGQUIT, ft_ctrl_slash);
	pid = fork();
	cmd->child = pid;
	if (pid == -1)
	{
		closing_all_fd(base);
		error_manager(base, 1, "Error process", 0);
	}
	else if (pid == 0)
	{
		switching_in_out(base, cmd);
		closing_all_fd(base);
		if (is_child_builtin(cmd) == 1)
		{
			if (exec_child_builtin(base, cmd) == 0)
				exit(EXIT_SUCCESS);
			exit(EXIT_FAILURE);
		}
		else
			launching_command(base, cmd);
	}
}

int	creating_child(t_cmd *cmd, t_base *base)
{
	if (is_parent_builtin(cmd) == 1)
	{
		if (exec_parent_builtin(base, cmd) == 0)
		{
			base->exit_status = EXIT_SUCCESS;
			return (1);
		}
		return (-1);
	}			
	else
		child_process(base, cmd);
	return (1);
}

int	exec_pipes(t_base *base)
{
	t_cmds	*cmds;
	int		process_status;

	process_status = 0;
	base->cmds = push_commands(base);
	cmds = base->cmds;
	while (cmds)
	{
		creating_child(cmds->cmd, base);
		cmds = cmds->next;
	}
	closing_all_fd(base);
	cmds = base->cmds;
	while (cmds)
	{
		waitpid(cmds->cmd->child, &process_status, 0);
		if (cmds->cmd && !is_parent_builtin(cmds->cmd)
			&& !WIFSIGNALED(process_status))
			g_signum = WEXITSTATUS(process_status);
		cmds = cmds->next;
	}
	base->exit_status = process_status;
	return (0);
}
