/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:54 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/29 16:05:38 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_builtin(t_cmd *cmd, t_base *base)
{
	int	signal;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->arg)
		signal = 0;
	else
		signal = ft_atoi(cmd->arg);
	// free all
	exit(signal);
}