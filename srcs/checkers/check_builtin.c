/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:29:55 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/31 13:32:29 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin_cmd(char *name, t_cmd *cmd)
{
    if (ft_equal_strs(name, cmd->content))
		return (1);
	return (0);
}