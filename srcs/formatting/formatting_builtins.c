/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:54:52 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/06 12:06:07 by lgosselk         ###   ########.fr       */
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
		cmd->first_arg->name = get_home_path(base);
		if (!cmd->first_arg->name)
			return (-1);
		return (1);
	}
	return (1);
}

static int	format_exit(t_cmd *cmd)
{
	int		i;
	t_arg	*arg;

	i = -1;
	arg = get_first_arg(cmd);
	while (arg->name[++i])
	{
		if (arg->name[i] < 48 || arg->name > 57)
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

static int	format_export(t_cmd *cmd)
{
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (arg->next)
	{
		arg = arg->next;
		while (arg)
		{
			ft_printf("export: '%s': not a valid identifier\n", arg->name);
			arg = arg->next;
		}
		return (0);
	}
	return (1);
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
			if (!format_cd(base, cmd))
				return (-1);
		if (is_builtin_cmd("exit", cmd))
			if (!format_exit(cmd))
				return (-1);
		if (is_builtin_cmd("export", cmd))
			if (!format_export(cmd))
				return (-1);
		if (is_builtin_cmd("env", cmd))
			if (!format_env(cmd))
				return (-1);
		token = get_next_builtin(token);
	}
}