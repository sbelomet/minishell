/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:24:08 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/22 15:55:03 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_path_or_curr(char *cmd, int res, char *path)
{
	int	i;

	if (res)
		return (1);
	if (ft_strchr(cmd, '/'))
		return (1);
	if (path[0] == ':' || path[ft_strlen(path) - 1] == ':')
		return (1);
	i = 0;
	while (path[++i])
	{
		if (path[i] == ':' && path[i - 1] == ':')
			return (1);
	}
	return (0);
}

int	ft_isbin(t_base *base, char *cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		res;
	int		i;

	path = ft_findvar_value(base, "$PATH");
	paths = ft_split(path, ':');
	res = 0;
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			res = 1;
		free(path);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	res = ft_is_path_or_curr(cmd, res, ft_findvar_value(base, "$PATH"));
	return (res);
}

char	*ft_try_namepath(t_base *base, char *cmd, char *res, int cmd_id)
{
	if (res)
		return (res);
	if (cmd_id == TOKEN_BIN && access(cmd, F_OK | X_OK) == 0)
	{
		if (res)
			free(res);
		res = ft_strdup(cmd);
		if (!res)
			ft_error(base);
		return (res);
	}
	return (NULL);
}

char	*ft_get_cmdpath(t_base *base, char *cmd, int cmd_id)
{
	char	**paths;
	char	*path;
	char	*tmp;
	char	*res;
	int		i;

	path = ft_findvar_value(base, "$PATH");
	paths = ft_split(path, ':');
	res = NULL;
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			res = ft_strdup(path);
		free(path);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	res = ft_try_namepath(base, cmd, res, cmd_id);
	return (res);
}
