/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:37:01 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 14:47:15 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_err_builtin(t_cmd *cmd)
{
	t_arg	*arg;
	int		count;

	count = 0;
	arg = get_first_arg(cmd);
	if (is_cd_builtin(cmd))
	{
		while (arg)
		{
			count++;
			arg = arg->next;
		}
	}
	if (count > 1)
	{
		ft_putstr_fd("cd: too many arguments.\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

void	format_command(t_base *base)
{
	format_builtins();
	format_cmds_args();
	format_binaries();
}