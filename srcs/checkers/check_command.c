/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:53:33 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 11:26:27 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cmd_bin(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->id == TOKEN_BIN)
		return (1);
	return (0);
}

int	is_cmd_builtin(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->id == TOKEN_BUILTIN)
		return (1);
	return (0);
}
