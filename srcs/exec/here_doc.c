/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:05:58 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/28 16:02:15 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_var(t_base *base, char *line, int *fd,
		int i)
{
	int		j;
	char	*var;
	char	*find_var;

	var = malloc((i + 1) * sizeof(char));
	if (!var)
		return ;
	j = -1;
	while (++j < i)
		var[j] = line[j];
	var[j] = '\0';
	find_var = ft_findvar_value(base, var);
	if (!find_var)
		return ;
	else
		write(fd[1], find_var, ft_strlen(find_var));
	free(var);
}

static int	handle_expand_heredoc(t_base *base, char *line,
		int *fd)
{
	int		i;

	while (*line)
	{
		if (*line == '$')
		{
			i = 0;
			while (line[i] && !ft_isspecial(line[i]))
				i++;
			if (i > 0)
				handle_var(base, line, fd, i);
		}
		write(fd[1], line, 1);
		line++;
	}
	return (1);
}

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
		handle_expand_heredoc(base, line, fd);
	else
		write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	return (0);
}

static void	handle_here_doc(t_base *base,
		t_redir *redir, int *fd)
{
	char	*line;

	ft_heredoc_signal();
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

	ft_merdique_signal();
	if (cmd != NULL && cmd->fd_in != 0)
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
	if (cmd != NULL)
		cmd->fd_in = fd[0];
	base->exit_status = status;
	return (0);
}
