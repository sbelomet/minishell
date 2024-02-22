/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:54 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 16:15:52 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_msg(char *arg, char *msg)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	if (arg)
		ft_putstr_fd("arg", 2);
	ft_putstr_fd(msg, 2);
}

static int	exit_with_arg(t_base *base, t_cmd *cmd)
{
	unsigned int	exit_code;

	exit_code = ft_atoi(cmd->first_arg->name);
	if (!exit_code)
	{
		exit_msg(cmd->first_arg->name, ": numeric argument required\n");
		ft_free(*base);
		exit(255);
	}
	else
	{
		if (cmd->first_arg->next)
		{
			exit_msg(NULL, "exit: too many arguments\n");
			return (-1);
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			ft_free(*base);
			exit(exit_code);
		}
	}
	return (1);
}

int	exit_builtin(t_base *base, t_cmd *cmd)
{
	if (cmd->first_arg)
	{
		if (exit_with_arg(base, cmd) == -1)
			return (1);
	}
	else
	{
		ft_free(*base);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(base->exit_status);
	}
	return (0);
}
