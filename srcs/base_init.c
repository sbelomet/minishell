/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:46:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/31 11:19:47 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_builtins(t_base *base)
{
	base->builtins = (char **)malloc(sizeof(char *) * 8);
	if (!base->builtins)
		ft_error(base, "malloc()");
	base->builtins[0] = ft_strdup("echo");
	base->builtins[1] = ft_strdup("cd");
	base->builtins[2] = ft_strdup("pwd");
	base->builtins[3] = ft_strdup("export");
	base->builtins[4] = ft_strdup("unset");
	base->builtins[5] = ft_strdup("env");
	base->builtins[6] = ft_strdup("exit");
	base->builtins[7] = NULL;
}

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
	ft_set_builtins(base);
}
