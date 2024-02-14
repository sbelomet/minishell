/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:33:42 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 14:10:16 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_single_child(t_base *base, t_token *token)
{
	t_cmd	*cmd;

	signal(SIGQUIT, SIG_DFL);
	cmd = get_token_class(token);
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (is_child_builtin(cmd))
	{
		if (exec_child_builtin(base, cmd))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	if (is_cmd_bin(cmd)) // REFACTORING
	{
		if (!cmd->path)
			return ; //g_error = 127 command not found;
		if (access(cmd->path, F_OK | X_OK) == 0)
			execve(cmd->path, get_args_tab(cmd->first_arg), base->env);
		else
			return ; // g_error = 127 command not found;
	}
	exit(EXIT_FAILURE);
}

static int	handle_token(t_base *base, t_token *token)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = get_next_cmd(token);
	ft_printf(STDOUT_FILENO, "cmd were checking: %s\n", cmd->name);
	if (!cmd)
		return (-1);
	if (is_parent_builtin(cmd) == 1)
	{
		ft_printf(STDOUT_FILENO, "cmd is builtin\n");
		if (exec_parent_builtin(base, cmd))
		{
			base->exit_status = EXIT_SUCCESS;
			return (1);
		}
	}
	pid = fork();
	if (pid == 0)
		exec_single_child(base, token);
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
	t_token	*token;

	ft_printf(STDOUT_FILENO, "we in exec single cmd\n");
	token = get_first_token(base);
	while (token)
	{
		handle_token(base, token);
		token = get_next_token_cmd(token);
	}
	return (1);
}
