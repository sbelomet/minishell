/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:30 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/29 15:43:54 by lgosselk         ###   ########.fr       */
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