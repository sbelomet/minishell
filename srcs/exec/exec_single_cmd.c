/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:33:42 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/19 10:30:24 by lgosselk         ###   ########.fr       */
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
	if (is_child_builtin(cmd) == 1)
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
		{
			printf("EXEC02kshgls\n");
			execve(cmd->path, get_args_tab(cmd->first_arg, cmd->path), base->env);
		}
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
	if (is_parent_builtin(token) == 1)
	{
		if (exec_parent_builtin(base, cmd))
		{
			base->exit_status = EXIT_SUCCESS;
			return (1);
		}
		return(-1);
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
	t_token	*tmp_token;

	printf("EXEC0 SINGLE\n");
	token = get_first_token(base);
	tmp_token = token;
	while (token && is_token_cmd(token))
	{
		handle_token(base, token);
		token = get_next_token_cmd(token);
	}
	token = tmp_token;
	return (1);
}
