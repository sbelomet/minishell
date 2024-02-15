/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:46:13 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/15 11:43:24 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_last_cmd_arg(t_base *base, t_token *last_token)
{
	t_cmd	*cmd;
	char	*res;
	t_arg	*arg;

	cmd = last_token->type;
	if (!cmd->first_arg)
	{
		if (cmd->path)
			res = ft_strdup(cmd->path);
		else
			res = ft_strdup(cmd->name);
		if (!res)
			ft_error(base, "malloc()");
		return (res);
	}
	arg = ft_last_arg(cmd->first_arg);
	res = ft_strdup(arg->name);
	if (!res)
		ft_error(base, "malloc()");
	return (res);
}

void	update_last_arg(t_base *base, t_token *last_token)
{
	int		i;
	t_var	*last_var;
	char	*res;

	while (last_token && is_token_cmd(last_token) == 0)
		last_token = last_token->prev;
	res = ft_get_last_cmd_arg(base, last_token);
	last_var = ft_findvar(base->first_var, "_");
	if (last_var != NULL)
	{
		free(last_var->value);
		last_var->value = ft_strdup(res);
	}
	i = -1;
	while (base->env[++i])
	{
		if (ft_strnstr(base->env[i], "_=", 2))
		{
			free(base->env[i]);
			base->env[i] = ft_strjoin("_=", res);
		}
	}
	free(res);
}
