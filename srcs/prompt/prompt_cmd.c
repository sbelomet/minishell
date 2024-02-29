/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:48 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 15:56:10 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_to_remind(char	*remind, char *buff)
{
	char	*temp;

	if (remind)
	{
		temp = remind;
		remind = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
	}
	else
		remind = ft_strdup(buff);
	return (remind);
}

char	*ft_read(int fd, char *remind)
{
	int		byte;
	char	*buff;

	buff = malloc((50 + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	byte = 1;
	while (byte != 0)
	{
		byte = read(fd, buff, 50);
		if (byte == -1)
		{
			free(buff);
			free(remind);
			return (NULL);
		}
		buff[byte] = '\0';
		remind = ft_to_remind(remind, buff);
	}
	free(buff);
	return (remind);
}

char	*get_next_line(int fd)
{
	char	*remind;

	if (fd < 0)
		return (0);
	remind = NULL;
	remind = ft_read(fd, remind);
	if (remind == NULL)
	{
		free(remind);
		return (NULL);
	}
	return (remind);
}

static void	handle_line(int *fd)
{
	char	*line;

	line = NULL;
	ft_heredoc_signal();
	while (!line)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf(1, "\033[1A> syntax error: unexpected end of file\n");
			exit(EXIT_FAILURE);
		}
		if (ft_strlen(line) <= 0)
		{
			free(line);
			line = NULL;
		}
	}
	write(fd[1], line, ft_strlen(line));
	free(line);
	exit(0);
}

int	prompt_cmd(t_base *base)
{
	int		pid;
	int		fd[2];
	char	*line;
	int		status;

	ft_merdique_signal();
	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
		handle_line(fd);
	waitpid(pid, &status, 0);
	close(fd[1]);
	line = get_next_line(fd[0]);
	if (WIFSIGNALED(status) || !(ft_strlen(line) > 0))
	{
		base->exit_status = 1;
		close(fd[0]);
		return (-1);
	}
	ft_lexer_start(base, ft_strtrim(line, " \n\t"));
	free(line);
	close(fd[0]);
	base->exit_status = status;
	return (0);
}
