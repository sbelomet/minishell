/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:54 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 14:44:00 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numerical(char *str)
{
	int	i;

	if (ft_equal_strs(str, "+") || ft_equal_strs(str, "-"))
		return (0);
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
		i++;
	if (i != ft_strlen(str))
		return (0);
	return (1);
}

static void	exit_msg(t_base *base, char *arg, char *msg)
{
	if (!base->pipe)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	if (arg)
		ft_putstr_fd("arg", 2);
	ft_putstr_fd(msg, 2);
}

static int	exit_with_arg(t_base *base, t_cmd *cmd)
{
	unsigned int	exit_code;

	if (!is_numerical(cmd->first_arg->name))
	{
		exit_msg(base, cmd->first_arg->name, ": numeric argument required\n");
		if (base->pipe)
			return (1);
		ft_free(*base);
		exit(255);
	}
	exit_code = ft_atoi(cmd->first_arg->name);
	if (cmd->first_arg->next)
	{
		exit_msg(base, NULL, "exit: too many arguments\n");
		return (-1);
	}
	else
	{
		if (base->pipe)
			return (1);
		ft_putstr_fd("exit\n", 1);
		ft_free(*base);
		exit(exit_code);
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
		if (base->pipe)
			return (0);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_free(*base);
		exit(base->exit_status);
	}
	return (0);
}
