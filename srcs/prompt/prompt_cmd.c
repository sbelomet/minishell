/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:48 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 12:13:42 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_line(t_base *base)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	line = readline("> ");
	if (ft_strlen(line) > 0)
		ft_lexer_start(base, ft_strtrim(line, " \n\t"));
	free(line);
	exit(0);
}

int	prompt_cmd(t_base *base)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
		handle_line(base);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		base->exit_status = 1;
		return (-1);
	}
	base->exit_status = status;
	return (0);
}
