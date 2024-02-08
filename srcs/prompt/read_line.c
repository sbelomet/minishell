/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 08:46:15 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/08 13:53:35 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_line(t_base *base, char *line)
{
	int	error;

	ft_lexer_start(base, line);
	if (!errors_lexer(base))
	{
		format_builtins(base);
		error = format_redirections(base);
		if (error == 0)
			exec_pipes(base);
		if (error == 1)
			base->exit_status = EXIT_FAILURE; // file not open
	}
	// remove tokens and cleanup for next line
}
