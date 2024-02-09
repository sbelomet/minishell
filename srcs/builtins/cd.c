/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:22 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/09 15:11:40 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (0);
	if (testing_path(home))
	{
		if (chdir(home) != 0)
		{
			perror("cd");
			return (0);
		}
		else
			update_env(base, "PWD", home);
		return (1);
	}
	else if (base->pipe)
		return (1);
	return (0);
}

int	cd_path(t_base *base, t_arg *arg)
{
	if (testing_path(arg->name))
	{
		if (chdir(arg->name) != 0)
		{
			perror("cd");
			return (0);
		}
		else
			update_env(base, "PWD", arg->name);
		return (1);
	}
	else if (base->pipe)
		return (1);
	return (0);
}

int exec_cd(t_base *base, t_cmd *cmd)
{
    t_arg *args;

	args = get_first_arg(cmd);
	if (args)
	{
		if (!cd_path(base, args))
			return (0);
	}	
	else
	{
		if (!cd_home(base))
			return (0);
	}
	return (1);
}