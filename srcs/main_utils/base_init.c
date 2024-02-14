/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:46:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/14 14:19:28 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_malloced_env(char **env)
{
	int		i;
	char	**array;

	i = 0;
	while (env[i])
		i++;
	array = (char **) malloc((i + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array[i] = 0;
	i = -1;
	while (env[++i])
	{
		array[i] = (char *) malloc(ft_strlen(env[i]));
		if (!array[i])
		{
			ft_free_array(array);
			return (NULL);
		}
		array[i] = ft_strdup(env[i]);
	}
	return (array);
}

void	ft_base_init(t_base *base, char **env)
{
	base->env = get_malloced_env(env);
	base->alloc = NULL;
	base->first_var = NULL;
	base->first_token = NULL;
	base->curdir = getcwd(NULL, 0);
	ft_get_env_vars(base, env);
	base->pipe = 0;
}
