/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:54:52 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 15:35:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			ft_printf(1, "exit\nexit: %s: numeric argumets required\n",
				arg->name); // exit from program, exit code = 255
	}
	if (is_numeric_arg(arg))
		return ; // exit from program, exit code = arg
	if (!is_numeric_arg(arg))
		ft_printf(1, "exit\nexit: %s: numeric argumets required\n", arg->name); // exit from program, exit code = 255
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
					ft_printf(1, "export: '%s': not a valid identifier\n",
						arg->name);
			}
		}
		arg = arg->next;
	}
}

void	format_builtins(t_base *base)
{
	t_cmd	*cmd;
	t_token	*token;

	token = get_first_builtin(base);
	while (token)
	{
		cmd = get_token_class(token);
		if (is_builtin_cmd("exit", cmd))
			format_exit(cmd);
		if (is_builtin_cmd("export", cmd))
			format_export(cmd);
		if (is_builtin_cmd("env", cmd))
			format_env(cmd);
		token = get_next_builtin(token);
	}
}
