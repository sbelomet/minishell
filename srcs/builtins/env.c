/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:39 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 15:06:21 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_env_join(t_base *base, char *name, char *value)
{
	char	*tmp;
	char	*res;

	res = NULL;
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		ft_error(base);
	if (!value)
		return (tmp);
	res = ft_strjoin(tmp, value);
	free(tmp);
	if (!res)
		ft_error(base);
	return (res);
}

static void	_print(t_base *base, t_var *env)
{
	char	*temp;

	while (env)
	{
		if (ft_equal_strs(env->name, "_"))
		{
			ft_putstr_fd("_=env\n", STDOUT_FILENO);
			env = env->next;
			continue ;
		}
		if (env->printable == ONLY_ENV || env->printable == BOTH)
		{
			temp = ft_env_join(base, env->name, env->value);
			ft_putstr_fd(temp, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free(temp);
			temp = NULL;
		}
		env = env->next;
	}
}

int	print_env(t_base *base, t_cmd *cmd)
{
	if (cmd->first_arg)
	{
		ft_putstr_fd("env: too many arguments.\n", 2);
		base->exit_status = 1;
		return (-1);
	}
	_print(base, base->first_var);
	return (0);
}
