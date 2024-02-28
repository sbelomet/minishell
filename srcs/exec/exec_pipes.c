/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:53 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/28 15:50:52 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	switching_input_output(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return ; // 1
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return; // 1
		close(cmd->fd_out);
	}
}

void	launching_command(t_base *base, t_cmd *cmd)
{
	if (execve(cmd->path, get_args_tab(cmd->first_arg, cmd->path), base->env) == -1)
	{
		base->exit_status = 127;
		exit(127);
	}
}

void	child_process(t_base *base, t_cmd *cmd)
{
	switching_input_output(cmd);
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

int	creating_child(t_cmd *cmd, t_base *base)
{
	int	pid;
	
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
	{
		signal(SIGINT, ft_ctrl_c2);
		signal(SIGQUIT, ft_ctrl_slash);
		pid = fork();
		cmd->child = pid;
		if (pid == -1)
		{
			closing_all_fd(base);
			base->exit_status = 1;
			return (-1);
		}
		else if (pid == 0)
		{
			child_process(base, cmd); // handle error
		}
	}
	return (1);
}

int	exec_pipes(t_base *base)
{
	t_cmds	*cmds;
	int			process_status;

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
	return (0);
}
