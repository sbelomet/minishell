/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:05 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/21 14:01:37 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_export_join(t_base *base, char *name, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin("declare -x ", name);
	if (!tmp)
		ft_error(base, "malloc()");
	res = ft_strjoin(tmp, "=\"");
	if (!res)
		ft_error(base, "malloc()");
	free(tmp);
	tmp = ft_strjoin(res, value);
	if (!tmp)
		ft_error(base, "malloc()");
	free(res);
	res = ft_strjoin(tmp, "\"");
	if (!res)
		ft_error(base, "malloc()");
	free(tmp);
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
			tmp = ft_export_join(base, var->name, var->value);
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
	//int		i;
	t_arg	*args;
	char	**array;

	args = cmd->first_arg;
	if (!base)
		return (0);
	while (args)
	{
		if (check_arg_export(args->name) == 0)
		{
			array = ft_split(args->name, '=');
			add_export(base, args, array);
			// free array;
		}
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
