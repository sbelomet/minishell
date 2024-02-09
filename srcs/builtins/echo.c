/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:30 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 11:35:36 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo(t_cmd *cmd)
{
	if (!cmd->arg)
		ft_putstr_fd("\n", cmd->fd_out);
	else
	{
		ft_putstr_fd(cmd->arg, cmd->fd_out);
		if (cmd->flags)
			ft_putstr_fd("\n", cmd->fd_out);
	}
	return (0);
}
