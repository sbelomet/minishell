/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:47:22 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 10:34:09 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*get_first_arg(t_cmd *cmd)
{
	if (cmd->first_arg)
		return (cmd->first_arg);
	return (NULL);
}
