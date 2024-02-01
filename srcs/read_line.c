/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 08:46:15 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 13:05:10 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_line(t_base *base, char *line)
{
	ft_lexer_start(base, line);
	if (!errors_lexer(base))
	{
		format_command(base);
	}
    // remove tokens and cleanup for next line
}