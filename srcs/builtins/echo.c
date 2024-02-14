/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:30 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 13:17:07 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd *cmd)
{
	int	flag_nl;

	flag_nl = 0;
	if (cmd->first_arg && ft_equal_strs(cmd->first_arg->name, "-n"))
	{	
		flag_nl = 1;
		cmd->first_arg = cmd->first_arg->next;
	}
	while (cmd->first_arg)
	{
		ft_putstr_fd(cmd->first_arg->name, STDOUT_FILENO);
		if (cmd->first_arg->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		cmd->first_arg = cmd->first_arg->next;
	}
	if (!flag_nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
