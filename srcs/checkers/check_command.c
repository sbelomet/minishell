/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:53:33 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 11:22:18 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cmd_bin(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->id /* EQUAL TOKEN_BINARY */)
		return (1);
	return (0);
}

int	is_cmd_builtin(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->id /* EQUAL TOKEN_BUILTIN */)
		return (1);
	return (0);
}