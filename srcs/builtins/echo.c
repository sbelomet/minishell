/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:30 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 10:13:36 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_n_flag(char *flag)
{
	int	i;

	if (!flag || ft_strlen(flag) < 2 || flag[0] != '-' || flag[1] != 'n')
		return (0);
	i = 2;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_base *base, t_cmd *cmd)
{
	int	flag_nl;

	(void)base;
	flag_nl = 0;
	if (cmd->first_arg && ft_is_n_flag(cmd->first_arg->name))
	{	
		flag_nl = 1;
		cmd->first_arg = cmd->first_arg->next;
		while (cmd->first_arg && ft_is_n_flag(cmd->first_arg->name))
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
