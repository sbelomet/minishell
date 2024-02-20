/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:53 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/19 10:27:28 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_base *base, t_token *token,
		int *fds, int in_fd)
{
	t_cmd	*curr_cmd;
    t_cmd   *next_cmd;

	signal(SIGQUIT, SIG_DFL);
	close(fds[0]);
    printf("DEBBUG00 CHILD\n");
    curr_cmd = get_token_class(token);
    next_cmd = get_next_cmd(token->next);
	dup_redir(curr_cmd, next_cmd, fds, in_fd);
	printf("DEBBUG01 CHILD\n");
	if (is_child_builtin(curr_cmd) == 1)
	{
		printf("DEBBUG00 CHILD BUILTIN\n");
		if (exec_child_builtin(base, get_token_class(token)))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	printf("DEBBUG02 CHILD\n");
	if (is_token_bin(token))
	{
		if (access(curr_cmd->path, F_OK | X_OK) == 0)
		{
			printf("DEBBUG04 CHILD\n");
			execve(curr_cmd->path,
                get_args_tab(curr_cmd->first_arg, curr_cmd->path), base->env);
		}
		else
		{
			printf("DEBBUG05 CHILD\n");
			return ; // 127;
		}
	}
	printf("DEBBUG CHILD END\n");
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

	if (is_parent_builtin(token) == 1)
	{
		if (exec_parent_builtin(base, get_token_class(token)))
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
	token = get_first_token(base);
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
