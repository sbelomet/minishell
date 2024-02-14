/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:03:48 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 14:11:02 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_line(t_base *base, char *line)
{
	if (!line)
		return ;
	// call lexer to add new token at the bottom of the list.
}

void	prompt_cmd(t_base *base)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	line = readline("> ");
	handle_line(base, line);
	free(line);
	exit(0);
}
