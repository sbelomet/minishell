/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:09:11 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 11:48:38 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_parent_builtin(t_token *token)
{
	t_cmd	*cmd;

	cmd = get_token_class(token);
	if (ft_equal_strs(cmd->name, "cd"))
		return (1);
	if (ft_equal_strs(cmd->name, "export")
		&& cmd->first_arg)
		return (1);
	if (ft_equal_strs(cmd->name, "unset"))
		return (1);
	if (ft_equal_strs(cmd->name, "exit"))
		return (1);
	return (-1);
}

int	is_child_builtin(t_cmd *cmd)
{
	if (ft_equal_strs(cmd->name, "echo"))
		return (1);
	if (ft_equal_strs(cmd->name, "pwd"))
		return (1);
	if (ft_equal_strs(cmd->name, "export")
		&& !cmd->first_arg)
		return (1);
	if (ft_equal_strs(cmd->name, "env"))
		return (1);
	return (-1);
}

int	exec_parent_builtin(t_base *base, t_cmd *cmd)
{
	if (ft_equal_strs(cmd->name, "cd"))
		return (exec_cd(base, cmd));
	if (ft_equal_strs(cmd->name, "export")
		&& cmd->first_arg)
		return (builtin_export(base, cmd));
	if (ft_equal_strs(cmd->name, "unset"))
		return (unset(base, cmd));
	if (ft_equal_strs(cmd->name, "exit"))
		return (exit_builtin(base, cmd));
	return (-1);
}

int	exec_child_builtin(t_base *base, t_cmd *cmd)
{
	if (ft_equal_strs(cmd->name, "echo"))
		return (echo(cmd));
	if (ft_equal_strs(cmd->name, "pwd"))
		return (pwd(base));
	if (ft_equal_strs(cmd->name, "export")
		&& !cmd->first_arg)
		return (builtin_export(base, cmd));
	if (ft_equal_strs(cmd->name, "env"))
		return (print_env(base, cmd));
	return (-1);
}
