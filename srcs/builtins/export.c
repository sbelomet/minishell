/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:05 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/22 15:53:31 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_export_join(t_base *base, char *name,
	char *value, int standalone)
{
	char	*tmp;
	char	*res;

	res = NULL;
	tmp = ft_strjoin("declare -x ", name);
	if (!tmp)
		ft_error(base);
	if (standalone)
		return (tmp);
	res = ft_strjoin(tmp, "=\"");
	free(tmp);
	if (!res)
		ft_error(base);
	tmp = ft_strjoin(res, value);
	free(res);
	if (!tmp)
		ft_error(base);
	res = ft_strjoin(tmp, "\"");
	free(tmp);
	if (!res)
		ft_error(base);
	return (res);
}

static void	ft_print_export(t_base *base)
{
	t_var	*var;
	char	*tmp;

	var = base->first_var;
	while (var)
	{
		if (var->printable == ONLY_EXPORT || var->printable == BOTH)
		{
			tmp = ft_export_join(base, var->name, var->value, var->standalone);
			ft_putstr_fd(tmp, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free(tmp);
			tmp = NULL;
		}
		var = var->next;
	}
}

static int	check_arg_export(char *arg)
{
	int	i;

	i = 1;
	// _1=1 can be possible
	if (arg[0] == '=' || (!(arg[0] >= 'a' && arg[0] <= 'z') &&
		!(arg[0] >= 'A' && arg[0] <= 'Z') && arg[0] != '_'))
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (i != 0 && (!(arg[i] >= 'a' && arg[i] <= 'z') &&
			!(arg[i] >= 'A' && arg[i] <= 'Z') && !(arg[i] >= '0' && arg[0] <= '9')))
			return (1);
		i++;
	}
	if (arg[i] == '=' && arg[i + 1] == '=')
		return (1);
	return (0);
}

static int	handle_export_args(t_base *base, t_cmd *cmd)
{
	t_arg	*args;

	args = cmd->first_arg;
	if (!base)
		return (0);
	while (args)
	{
		if (check_arg_export(args->name) == 0)
		{
			if (ft_strchr(args->name, '=') != NULL)
				add_export(base, ft_split(args->name, '='), 1);
			else
				add_export(base, ft_split(args->name, '='), 0);
		}
		else
		{} // print error	
		args = args->next;
	}
	return (0);
}

int	builtin_export(t_base *base, t_cmd *cmd)
{
	if (!cmd->first_arg)
		ft_print_export(base);
	else
		handle_export_args(base, cmd);
	return (0);
}
