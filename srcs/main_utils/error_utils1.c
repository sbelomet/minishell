/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:46:45 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/12 11:22:51 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_base *base, char *message)
{
	perror(message);
	ft_free(*base);
	exit(-1);
}

void	ft_free_vars(t_base base)
{
	t_var	*tmp1;
	t_var	*tmp2;

	tmp1 = base.first_var;
	if (tmp1)
	{
		while (tmp1)
		{
			tmp2 = tmp1->next;
			free(tmp1->name);
			free(tmp1->value);
			free(tmp1);
			tmp1 = tmp2;
		}
	}	
}

void	ft_free(t_base base)
{
	ft_free_vars(base);
	ft_free_array(base.env);
	if (base.curdir)
		free(base.curdir);
}
