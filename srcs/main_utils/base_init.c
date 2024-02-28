/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:46:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/28 16:02:41 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_malloced_env(t_base *base, char **env)
{
	int		i;
	char	**array;

	i = 0;
	while (env[i])
		i++;
	array = (char **)ft_malloc((i + 1) * sizeof(char *), &base->alloc);
	if (!array)
		return (NULL);
	array[i] = 0;
	i = -1;
	while (env[++i])
	{
		array[i] = (char *)ft_malloc(ft_strlen(env[i]), &base->alloc);
		if (!array[i])
		{
			ft_free_array(array);
			return (NULL);
		}
		array[i] = ft_strdup_allocated(env[i], &base->alloc);
	}
	return (array);
}

static void	push_exit_status_env(t_base *base)
{
	char	*name;
	char	*value;
	t_var	*status_env;

	name = ft_strdup("?");
	value = ft_strdup("0");
	if (!name || !value)
		ft_error(base);
	status_env = ft_new_var_node(name, value, NONE, 0);
	if (!status_env)
		ft_error(base);
	ft_add_var_node(base, status_env);
}

void	ft_base_init(t_base *base, char **env)
{
	base->alloc = NULL;
	base->env = get_malloced_env(base, env);
	if (!base->env)
		ft_error(base);
	ft_incr_shell_level(base);
	base->first_var = NULL;
	base->first_token = NULL;
	base->curdir = getcwd(NULL, 0);
	ft_get_env_vars(base, base->env);
	push_exit_status_env(base);
	base->pipe = 0;
}
