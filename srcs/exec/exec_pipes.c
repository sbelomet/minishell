/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:53 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 14:10:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_base *base, t_token *token,
		int *fds, int in_fd)
{
	t_cmd	*cmd;

	signal(SIGQUIT, SIG_DFL);
	close(fds[0]);
	dup_redir(token, fds, in_fd);
	cmd = get_token_class(token);
	if (is_child_builtin(cmd))
	{
		if (exec_child_builtin(base, cmd))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	if (is_cmd_bin(cmd))
	{
		if (!cmd->path)
		{
			base->exit_status = 127;
			return ;
		}
		if (execve(cmd->path, get_args_tab(cmd->first_arg), base->env) == -1)
		{
			base->exit_status = 127;
			return ;
		}
	}
	exit(EXIT_FAILURE);
}

static int	exec_parent(t_base *base, int pid, int *fds, int *std_pipe)
{
	close(fds[1]);
	waitpid(pid, &(base->exit_status), 0);
	base->exit_status = get_exit_status(base->exit_status);
	if (*std_pipe != 0)
		close(*std_pipe);
	*std_pipe = fds[0];
	return (0);
}

static int	handle_token(t_base *base, t_token *token,
		int *fds, int *std_pipe)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = get_next_cmd(token);
	if (!cmd)
		return (-1);
	if (is_parent_builtin(cmd))
	{
		if (exec_parent_builtin(base, cmd))
		{
			base->exit_status = EXIT_SUCCESS;
			return (1);
		}
	}
	pid = fork();
	if (pid == 0)
		exec_child(base, token, fds, *std_pipe);
	else
	{
		close_streams(cmd);
		exec_parent(base, pid, fds, std_pipe);
	}
	return (1);
}

int	exec_pipes(t_base *base)
{
	int		fd[2];
	t_token	*token;
	int		std_pipe;

	if (pipe(fd) < 0)
		return (-1);
	std_pipe = 0;
	token = get_first_token(base);
	while (token)
	{
		handle_token(base, token, fd, &std_pipe);
		token = get_next_token_cmd(token);
	}
	return (1);
}
