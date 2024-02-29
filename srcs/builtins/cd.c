/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:22 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/29 11:07:26 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	testing_path(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		perror("cd");
	else
	{
		if (S_ISDIR(st.st_mode) != 0)
		{
			if (access(path, X_OK) == -1)
			{
				perror("cd");
				return (0);
			}
			else
				return (1);
		}
	}
	return (0);
}

int	cd_home(t_base *base)
{
	char	*home;

	home = get_home_path(base);
	if (!home)
		return (-1);
	if (testing_path(home))
	{
		if (chdir(home) != 0)
		{
			perror("cd");
			return (-1);
		}
		else
			update_pwd_env(base, home);
		return (1);
	}
	else if (base->pipe)
		return (1);
	return (-1);
}

int	cd_path(t_base *base, t_arg *arg)
{
	char	*path;

	if (testing_path(arg->name))
	{
		if (chdir(arg->name) != 0)
		{
			perror("cd");
			return (-1);
		}
		else
		{
			path = get_current_path();
			if (!path)
			{
				perror("Couldn't retrieve current directory");
				return (-1);
			}
			else
				update_pwd_env(base, path);
		}
		return (1);
	}
	else if (base->pipe)
		return (1);
	return (-1);
}

int	exec_cd(t_base *base, t_cmd *cmd)
{
	t_arg	*args;

	args = get_first_arg(cmd);
	if (args)
	{
		if (cd_path(base, args) == -1)
		{
			base->exit_status = 1;
			return (1);
		}
	}
	else
	{
		if (cd_home(base) == -1)
		{
			base->exit_status = 1;
			return (1);
		}
	}
	return (0);
}
