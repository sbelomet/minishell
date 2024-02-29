/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:33:42 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 15:10:03 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_permission(char *path)
{
	struct stat	file;

	if (stat(path, &file) == 0)
	{
		if (S_ISREG(file.st_mode) && (file.st_mode & S_IXUSR))
			return (0);
		return (126);
	}
	return (127);
}

static void	exec_single_child(t_base *base, t_cmd *cmd)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (is_child_builtin(cmd) == 1)
	{
		if (exec_child_builtin(base, cmd) == 0)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	else if (is_cmd_bin(cmd))
	{
		base->exit_status = check_permission(cmd->path);
		if (base->exit_status == 126 || base->exit_status == 127)
		{
			ft_printf(1, "command not found: %s\n", cmd->name);
			exit(base->exit_status);
		}
		if (execve(cmd->path, get_args_tab(cmd->first_arg, cmd->path),
				base->env) == -1)
		{
			base->exit_status = 127;
			exit(127);
		}
	}
	exit(EXIT_FAILURE);
}

static int	handle_token(t_base *base, t_cmd *cmd)
{
	pid_t	pid;

	signal(SIGINT, ft_ctrl_c2);
	signal(SIGQUIT, ft_ctrl_slash);
	if (is_parent_builtin(cmd) == 1)
	{
		if (exec_parent_builtin(base, cmd) == 0)
		{
			base->exit_status = EXIT_SUCCESS;
			return (1);
		}
		return (-1);
	}
	pid = fork();
	if (pid == 0)
		exec_single_child(base, cmd);
	else
	{
		waitpid(pid, &(base->exit_status), 0);
		base->exit_status = get_exit_status(base->exit_status);
		close_streams(cmd);
	}
	return (1);
}

int	exec_single_cmd(t_base *base)
{
	t_cmds	*cmds;

	base->cmds = push_commands(base);
	cmds = base->cmds;
	while (cmds)
	{
		handle_token(base, cmds->cmd);
		cmds = cmds->next;
	}
	return (1);
}
