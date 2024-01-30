/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:47:22 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/30 11:51:31 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*get_first_arg(t_cmd *cmd)
{
	if (cmd->first_arg)
		return (cmd->first_arg);
	return (NULL);
}