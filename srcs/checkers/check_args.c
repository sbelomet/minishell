/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:56:21 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 14:08:58 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric_arg(t_arg *arg)
{
	int	i;

	i = -1;
	while (arg->name[++i])
	{
		if (arg->name[i] < 48 || arg->name[i] > 57)
			return (0);
	}
	return (1);
}
