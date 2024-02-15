/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:39 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/15 12:04:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_join(t_base *base, char *name, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		ft_error(base, "malloc()");
	res = ft_strjoin(tmp, value);
	if (!res)
		ft_error(base, "malloc()");
	free(tmp);
	return (res);
}

int	print_env(t_base *base, t_cmd *cmd)
{
	t_var	*env;
	char	*temp;

	if (cmd->first_arg)
	{
		ft_putstr_fd("env: too many arguments.\n", 2);
		return (-1);
	}
	env = base->first_var;
	while (env)
	{
		if (ft_equal_strs(env->name, "_"))
		{
			ft_putstr_fd("_=env\n", STDOUT_FILENO);
			env = env->next;
			continue ;
		}
		temp = ft_env_join(base, env->name, env->value);
		ft_putstr_fd(temp, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
		free(temp);
		temp = NULL;
	}
	return (0);
}
