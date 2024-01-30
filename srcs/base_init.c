/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:46:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/26 15:27:23 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_curdir(t_base *base)
{
	char	*pwd;
	int		i;

	pwd = getcwd(NULL, 0);
	ft_revstr(pwd);
	i = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
		{
			base->curdir = ft_substr(pwd, 0, i);
			ft_revstr(base->curdir);
			free(pwd);
			return ;
		}
		i++;
	}
}

void	ft_base_init(t_base *base, char **env)
{
	base->env = env;   
    base->alloc = NULL;
	base->first_var = NULL;
	ft_get_env_vars(base, env);
	ft_get_curdir(base);
}
