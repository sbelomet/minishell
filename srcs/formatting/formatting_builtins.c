/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:54:52 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/07 13:20:48 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	format_cd(t_base *base, t_cmd *cmd)
{
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (!arg)
		cmd->first_arg->name = get_home_path(base);
}

static void	format_exit(t_cmd *cmd)
{
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (!arg)
		return ; // exit from program, exit code = 0
	if (arg->next)
	{
		if (is_numeric_arg(arg) && (!is_numeric_arg(arg->next)
			|| is_numeric_arg(arg->next)))
			ft_putstr_fd("exit\nexit: too many arguments.\n", STDOUT_FILENO); // no exit, exit code = 1
		if (!is_numeric_arg(arg) && (is_numeric_arg(arg->next)
			|| !is_numeric_arg(arg->next)))
			ft_printf("exit\nexit: %s: numeric argumets required\n", arg->name); // exit from program, exit code = 255
	}
	if (is_numeric_arg(arg))
		return ; // exit from program, exit code = arg
	if (!is_numeric_arg(arg))
		ft_printf("exit\nexit: %s: numeric argumets required\n", arg->name); // exit from program, exit code = 255
}

static void	format_exit(t_cmd *cmd)
{
	int		i;
	t_arg	*arg;

	i = -1;
	arg = get_first_arg(cmd);
	while (arg->name[++i])
	{
		if (arg->name[i] < 48 || arg->name > 57)
			ft_putstr_fd("exit\nexit: numeric argumets required\n", STDOUT_FILENO);
	}
	i = 0;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	if (i > 1)
		ft_putstr_fd("exit\nexit: too many arguments.\n", STDOUT_FILENO);
}

static void	format_env(t_cmd *cmd)
{
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (arg)
		ft_putstr_fd("env: too many arguments.\n", STDOUT_FILENO);
}

static void	format_export(t_cmd *cmd)
{
	int		i;
	t_arg	*arg;

	arg = get_first_arg(cmd);
	if (!arg)
		return ;
	while (arg)
	{
		i = -1;
		while (arg->name[++i])
		{
			if (arg->name[i] == '=' && !arg->name[i + 1])
			{
				arg = arg->next;
				if (arg)
					ft_printf("export: '%s': not a valid identifier\n", arg->name);
			}
		}
		arg = arg->next;
	}
}

int	format_builtins(t_base *base)
{
	t_cmd	*cmd;
	t_token	*token;

	token = get_first_builtin(token);
	while (token)
	{
		cmd = get_token_class(token);
		if (is_builtin_cmd("cd", cmd))
			format_cd(base, cmd);
		if (is_builtin_cmd("exit", cmd))
			format_exit(cmd);
		if (is_builtin_cmd("export", cmd))
			format_export(cmd);	
		if (is_builtin_cmd("env", cmd))
			format_env(cmd);
		token = get_next_builtin(token);
	}
}