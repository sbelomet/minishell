/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:05 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 11:10:53 by lgosselk         ###   ########.fr       */
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
	if (arg[0] == '=' || (!(arg[0] >= 'a' && arg[0] <= 'z')
			&& !(arg[0] >= 'A' && arg[0] <= 'Z') && arg[0] != '_'))
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if ((!(arg[i] >= 'a' && arg[i] <= 'z')
				&& !(arg[i] >= 'A' && arg[i] <= 'Z')
				&& !(arg[i] >= '0' && arg[i] <= '9')))
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
	int		exit_code;

	exit_code = 0;
	args = cmd->first_arg;
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
		{
			exit_code = -1;
			print_export_error(base, args);
		}
		args = args->next;
	}
	return (exit_code);
}

int	builtin_export(t_base *base, t_cmd *cmd)
{
	if (!cmd->first_arg)
		ft_print_export(base);
	else
	{
		if (handle_export_args(base, cmd) == -1)
		{
			base->exit_status = 1;
			return (-1);
		}
	}
	return (0);
}
