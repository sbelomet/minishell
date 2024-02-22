/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:53 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/22 10:43:15 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_base *base, t_token *token,
		int *fds, int in_fd)
{
	int		status;
	t_cmd	*curr_cmd;
	t_cmd	*next_cmd;

	close(fds[0]);
	curr_cmd = get_token_class(token);
	next_cmd = get_next_cmd(token->next);
	dup_redir(curr_cmd, next_cmd, fds, in_fd);
	if (is_child_builtin(curr_cmd) == 1)
	{
		if (exec_child_builtin(base, get_token_class(token)) == 0)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	status = check_permission(curr_cmd->path);
	if (status == 126 || status == 127)
	{
		base->exit_status = status;
		exit(status);
	}
	execve(curr_cmd->path, get_args_tab(curr_cmd->first_arg, curr_cmd->path),
		base->env);
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

	signal(SIGINT, ft_ctrl_c2);
	signal(SIGQUIT, ft_ctrl_slash);
	if (is_parent_builtin(token) == 1)
	{
		if (exec_parent_builtin(base, get_token_class(token)) == 0)
		{
			base->exit_status = EXIT_SUCCESS;
			return (1);
		}
		return (-1);
	}
	pid = fork();
	if (pid == 0)
		exec_child(base, token, fds, *std_pipe);
	else
	{
		close_streams(get_token_class(token));
		exec_parent(base, pid, fds, std_pipe);
	}
	return (1);
}

int	exec_pipes(t_base *base)
{
	int		fd[2];
	t_token	*token;
	int		std_pipe;
	t_token	*tmp_token;

	std_pipe = 0;
	token = get_first_token_cmd_no_skip(base);
	tmp_token = token;
	while (token && is_token_cmd(token))
	{
		if (pipe(fd) < 0)
			return (-1);
		handle_token(base, token, fd, &std_pipe);
		token = get_next_token_cmd(token);
	}
	token = tmp_token;
	return (1);
}
