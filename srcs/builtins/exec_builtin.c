/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:09:11 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/07 16:16:44 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int exec_parent_builtin(t_cmd *cmd)
{
    if (ft_equal_strs(cmd->name, "cd"))
    {

    }
}

int exec_child_builtin(t_cmd *cmd)
{
    if (ft_equal_strs(cmd->name, "echo"))
    {

    }
}