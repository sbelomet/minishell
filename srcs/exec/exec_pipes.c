/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:35:53 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/27 15:49:26 by lgosselk         ###   ########.fr       */
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

/*int	is_parent_builtin_2(t_cmd	*cmd)
{
	if (ft_equal_strs(cmd->name, "cd"))
		return (1);
	if (ft_equal_strs(cmd->name, "export")
		&& cmd->first_arg)
		return (1);
	if (ft_equal_strs(cmd->name, "unset"))
		return (1);
	if (ft_equal_strs(cmd->name, "exit"))
		return (1);
	return (-1);
}

int	is_child_builtin_2(t_cmd *cmd)
{
	if (ft_equal_strs(cmd->name, "echo"))
		return (1);
	if (ft_equal_strs(cmd->name, "pwd"))
		return (1);
	if (ft_equal_strs(cmd->name, "export")
		&& !cmd->first_arg)
		return (1);
	if (ft_equal_strs(cmd->name, "env"))
		return (1);
	return (-1);
}

int	exec_parent_builtin_2(t_base *base, t_cmd *cmd)
{
	if (ft_equal_strs(cmd->name, "cd"))
		return (exec_cd(base, cmd));
	if (ft_equal_strs(cmd->name, "export")
		&& cmd->first_arg)
		return (builtin_export(base, cmd));
	if (ft_equal_strs(cmd->name, "unset"))
		return (unset(base, cmd));
	if (ft_equal_strs(cmd->name, "exit"))
		return (exit_builtin(base, cmd));
	return (-1);
}

int	exec_child_builtin_2(t_base *base, t_cmd *cmd)
{
	if (ft_equal_strs(cmd->name, "echo"))
		return (echo(cmd));
	if (ft_equal_strs(cmd->name, "pwd"))
		return (pwd(base));
	if (ft_equal_strs(cmd->name, "export")
		&& !cmd->first_arg)
		return (builtin_export(base, cmd));
	if (ft_equal_strs(cmd->name, "env"))
		return (print_env(base, cmd));
	return (-1);
}

void	closing_fd_if_redirections(t_base *base)
{
	t_cmd	*cmd;
	t_token	*token;

	token = base->first_token;
	while (token)
	{
		if (is_token_cmd(token))
		{
			cmd = get_token_class(token);
			if (cmd->fd_in > 1)
			close(STDIN_FILENO);
		}
		token = token->next;
	}
}

void	closing_all_fd(t_base *base)
{
	t_token	*token;
	t_cmd	*cmd;

	token = get_first_token_cmd(base);
	while (token)
	{
		cmd = get_token_class(token);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		token = token->next;
	}
}

void	switching_input_output(t_cmd **cmd)
{
	if ((*cmd)->fd_in == 0)
	{
		if (dup2((*cmd)->fd_in, STDIN_FILENO) < 0)
			return ; // 1
		close((*cmd)->fd_in);
	}
	if ((*cmd)->fd_out > 1)
	{
		if (dup2((*cmd)->fd_out, STDOUT_FILENO) < 0)
			return; // 1
		close((*cmd)->fd_out);
	}
}

void	launching_command(t_base *base, t_cmd **cmd)
{
	if (execve((*cmd)->path, get_args_tab((*cmd)->first_arg, (*cmd)->path), base->env) == -1)
		return ; //127 
}

void	child_process(t_base *base, t_cmd **cmd)
{
	switching_input_output(cmd);
	closing_all_fd(base);
	if (is_child_builtin_2(*cmd))
		exec_child_builtin_2(base, *cmd);
	else
		launching_command(base, cmd);
}

static void	creating_pipes(t_base *base)
{
    t_cmd	*cmd;
	int		fd[2];
	t_token	*token;
	t_cmd	*next_cmd;

	token = get_first_token_cmd();
	printf("DEBBUG10\n");
	while (token && is_token_cmd(token))
	{
		printf("DEBBUG11\n");
		if (pipe(fd) == -1)
			return ;
		cmd = get_token_class(token);
		printf("DEBBUG12\n");
		cmd->fd_out = fd[1];
		printf("DEBBUG13\n");
		token = get_next_token_cmd(token);
		printf("DEBBUG14\n");
		next_cmd = get_token_class(token);
		printf("DEBBUG15\n");
		next_cmd->fd_in = fd[0];
	}
	printf("DEBBUG16\n");
	closing_fd_if_redirections(base);
	printf("DEBBUG17\n");
}

void	creating_child(t_cmd **cmd, t_base *base)
{
	int	pid;

	if (is_parent_builtin_2(*cmd))
		exec_parent_builtin_2(base, *cmd);
	else
	{
		signal(SIGINT, ft_ctrl_c2);
		signal(SIGQUIT, ft_ctrl_slash);
		pid = fork();
		(*cmd)->child = pid;
		if (pid == -1)
		{
			closing_all_fd(base);
			return ; //error_manager
		}
		else if (pid == 0)
			child_process(base, cmd);
	}
}

int	exec_pipes(t_base *base)
{
	t_cmd	*cmd;
	t_token	*token;
	int		process_status;

	process_status = 0;
	printf("DEBBUG00\n");
	token = get_first_token_cmd_no_skip(base);
	printf("DEBBUG01\n");
	creating_pipes(base);
	printf("DEBBUG02\n");
	while (token && is_token_cmd(token))
	{
		printf("DEBBUG03\n");
		cmd = get_token_class(token);
		creating_child(&cmd, base);
		printf("DEBBUG04\n");
		token = get_next_token_cmd(token);
	}
	printf("DEBBUG04\n");
	closing_all_fd(base);
	printf("DEBBUG05\n");
	token = get_first_token_cmd(base);
	printf("DEBBUG06\n");
	while (token)
	{
		printf("DEBBUG07\n");
		cmd = get_token_class(token);
		waitpid(cmd->child, &process_status, 0);
		if (cmd && !is_parent_builtin_2(cmd)
			&& !WIFSIGNALED(process_status))
			g_signum = WEXITSTATUS(process_status);
		printf("DEBBUG08\n");
		token = get_next_token_cmd(token);
	}
	return (0);
}*/
