/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:33:42 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 12:23:41 by sbelomet         ###   ########.fr       */
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

static void	exec_single_child(t_base *base, t_token *token)
{
	t_cmd	*cmd;
	int		status;

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
	else if (is_cmd_bin(cmd))
	{
		status = check_permission(cmd->path);
		if (status == 126 || status == 127)
		{
			base->exit_status = status;
			exit(status);
		}
		execve(cmd->path, get_args_tab(cmd->first_arg, cmd->path), base->env);
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
		return (-1);
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

	token = get_first_token_cmd(base);
	tmp_token = token;
	while (token && is_token_cmd(token))
	{
		handle_token(base, token);
		token = get_next_token_cmd(token);
	}
	token = tmp_token;
	return (1);
}
