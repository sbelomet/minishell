/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:06:26 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 12:56:44 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_current_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("Couldn't retrieve current directory");
	return (path);
}

char	*get_home_path(t_base *base)
{
	t_var	*env_var;

	env_var = ft_findvar(base->first_var, "HOME");
	return (env_var->value);
}