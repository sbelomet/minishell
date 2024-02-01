/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:54:52 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 16:06:49 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	format_cd(t_base *base, t_cmd *cmd)
{
	t_arg	*arg;
	int		count;

	count = 0;
	arg = get_first_arg(cmd);
	if (!arg)
	{
		cmd->arg = get_home_path(base);
		return (1);
	}
	return (1);
	// handle cd options later
}

static int	format_exit(t_cmd *cmd)
{
	int		i;
	t_arg	*arg;

	i = -1;
	arg = get_first_arg(cmd);
	while (arg->value[++i])
	{
		if (arg->value[i] < 48 || arg->value > 57)
		{
			ft_putstr_fd("exit: numeric argumets required\n", STDOUT_FILENO);
			return (1);
		}
	}
	i = 0;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	if (i > 1)
	{
		ft_putstr_fd("exit: too many arguments.\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

static int	format_env(t_cmd *cmd)
{
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (arg)
	{
		ft_putstr_fd("exit: too many arguments.\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

static int	format_echo(t_cmd *cmd)
{
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (arg)
	{
		ft_putstr_fd("exit: too many arguments.\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
	// TO DO
}

int	format_builtins(t_base *base)
{
	t_cmd	*cmd;
	t_token	*token;

	token = get_first_builtin(token);
	while (token)
	{
		cmd = get_token_class(token);
		if (is_builtin_cmd("cd",cmd))
			format_cd(base, cmd);
		if (is_builtin_cmd("exit", cmd))
			format_exit(cmd);
		if (is_builtin_cmd("echo", cmd))
		{
			// strjoin all args and check for flag
		}
		if (is_builtin_cmd("env", cmd))
			format_env(cmd);
		token = get_next_builtin(token);
	}
}