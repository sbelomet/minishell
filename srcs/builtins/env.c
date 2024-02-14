/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:39 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/14 15:08:31 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_join(char *name, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	if (!res)
		return (NULL);
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
	} // return (-1) if args or print env anyway?
	env = base->first_var;
	while (env)
	{
		temp = ft_env_join(env->name, env->value);
		if (!temp)
			ft_error(base, "malloc()");
		ft_putstr_fd(temp, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
		free(temp);
		temp = NULL;
	}
	return (0);
}
