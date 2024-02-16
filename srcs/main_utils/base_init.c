/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:46:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/16 12:58:18 by sbelomet         ###   ########.fr       */
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

char	*ft_strjoin_shlvl(t_base *base, int shlvl)
{
	char	*res;

	if (++shlvl > 999)
		shlvl = 0;
	res = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	if (!res)
		ft_error(base, "malloc()");
	return (res);
}

void	ft_incr_shell_level(t_base *base)
{
	int		i;
	int		j;
	char	*shlvl;
	int		shlvl_int;

	i = -1;
	while (base->env[++i])
	{
		if (ft_strnstr(base->env[i], "SHLVL=", 6))
		{
			j = 6;
			while (base->env[i][j])
				j++;
			if (j != 6)
			{
				shlvl = ft_substr(base->env[i], 6, j);
				if (!shlvl)
					ft_error(base, "malloc()");
				shlvl_int = ft_atoi(shlvl);
				free(base->env[i]);
				base->env[i] = ft_strjoin_shlvl(base, shlvl_int);
			}
			break ;
		}
	}
}

void	ft_base_init(t_base *base, char **env)
{
	base->env = get_malloced_env(env);
	if (!base->env)
		ft_error(base, "malloc()");
	ft_incr_shell_level(base);
	base->alloc = NULL;
	base->first_var = NULL;
	base->first_token = NULL;
	base->curdir = getcwd(NULL, 0);
	ft_get_env_vars(base, base->env);
	base->pipe = 0;
}
