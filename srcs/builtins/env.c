/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:39 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/29 16:00:23 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_env(t_var *env_list)
{
	char	*temp;

	while (env_list)
	{
		temp = ft_strjoin(env_list->name, env_list->value);
		ft_putstr_fd(temp, STDOUT_FILENO);
		env_list = env_list->next;
		free(temp);
		temp = NULL;
	}
	return (0);
}