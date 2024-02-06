/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:05:58 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/05 11:25:21 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_input(t_base *base, t_redir *redir,
		char *line, int	*fd)
{
	if (!line || ft_equal_strs(line, redir->limiter))
	{
		if (line)
			free(line);
		return (1);
	}
	if (ft_strchr(line, '$'))
		return (NULL); // Change for expand function	
	else
		write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	return (0);
}

static void	handle_here_doc(t_base *base,
		t_redir *redir, int *fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (handle_input(base, redir, line, fd))
			break ;
		free(line);
	}
	exit(0);
}

int	init_heredoc(t_base *base, t_redir *redir, t_cmd *cmd)
{
	int		pid;
	int		fd[2];
	int		status;

	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
		handle_here_doc(base, redir, fd);
	waitpid(pid, &status, 0);
	close(fd[1]);
	if (WIFSIGNALED(status))
	{
		base->exit_status = 1;
		close(fd[0]);
		return (-2);
	}
	cmd->fd_in = fd[0];
	return (0);
}