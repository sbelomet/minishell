/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:29:55 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 11:41:52 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cd_builtin(t_cmd *cmd)
{
	if (ft_equal_strs("cd", cmd->content, 2))
		return (1);
	return (0);
}

int	is_echo_builtin(t_cmd *cmd)
{
	if (ft_equal_strs("echo", cmd->content, 4))
		return (1);
	return (0);
}

int	is_pwd_builtin(t_cmd *cmd)
{
	if (ft_equal_strs("pwd", cmd->content, 3))
		return (1);
	return (0);
}

int	is_env_builtin(t_cmd *cmd)
{
	if (ft_equal_strs("env", cmd->content, 3))
		return (1);
	return (0);
}

int	is_export_builtin(t_cmd *cmd)
{
	if (ft_equal_strs("export", cmd->content, 6))
		return (1);
	return (0);
}