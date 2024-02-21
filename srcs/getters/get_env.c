/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:06:26 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 12:20:04 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*get_home_path(t_base *base)
{
	t_var	*env_var;

	env_var = ft_findvar(base->first_var, "HOME");
	if (!env_var)
		return (NULL);
	return (env_var->value);
}
