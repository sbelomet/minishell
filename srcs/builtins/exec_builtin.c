/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:09:11 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 13:13:06 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_parent_builtin(t_cmd *cmd)
{
    if (ft_equal_strs(cmd->name, "cd"))
		return (1);
	if (ft_equal_strs(cmd->name, "export"))
		return (1);
	if (ft_equal_strs(cmd->name, "unset"))
		return (1);
	if (ft_equal_strs(cmd->name, "exit"))
		return (1);
	return (-1);
}

int is_child_builtin(t_cmd *cmd)
{
    if (ft_equal_strs(cmd->name, "echo"))
		return (1);
	if (ft_equal_strs(cmd->name, "pwd"))
		return (1);
	if (ft_equal_strs(cmd->name, "export"))
		return (1);
	if (ft_equal_strs(cmd->name, "env"))
		return (1);
	return (-1);
}

int exec_parent_builtin(t_base *base, t_cmd *cmd)
{
    if (ft_equal_strs(cmd->name, "cd"))
		return (1);//
	if (ft_equal_strs(cmd->name, "export"))
		return (1);//
	if (ft_equal_strs(cmd->name, "unset"))
		return (1);//
	if (ft_equal_strs(cmd->name, "exit"))
		return (1);//
	return (-1);
}

int exec_child_builtin(t_base *base, t_cmd *cmd)
{
    if (ft_equal_strs(cmd->name, "echo"))
		return (1);//
	if (ft_equal_strs(cmd->name, "pwd"))
		return (1);///
	if (ft_equal_strs(cmd->name, "export"))
		return (1);//
	if (ft_equal_strs(cmd->name, "env"))
		return (1);//
	return (-1);
}