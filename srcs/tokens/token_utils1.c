/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:24:08 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/16 11:07:07 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltin(char *cmd)
{
	if (ft_equal_strs("echo", cmd))
		return (1);
	if (ft_equal_strs("cd", cmd))
		return (1);
	if (ft_equal_strs("pwd", cmd))
		return (1);
	if (ft_equal_strs("export", cmd))
		return (1);
	if (ft_equal_strs("unset", cmd))
		return (1);
	if (ft_equal_strs("env", cmd))
		return (1);
	if (ft_equal_strs("exit", cmd))
		return (1);
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
	return (res);
}

char	*ft_try_namepath(t_base *base, char *cmd, char *res)
{
	if (!res)
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			if (res)
				free(res);
			res = ft_strdup(cmd);
			if (!res)
				ft_error(base, "malloc()");
		}
	}
	return (res);
}

char	*ft_get_cmdpath(t_base *base, char *cmd)
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
	res = ft_try_namepath(base, cmd, res);
	return (res);
}

int	ft_get_redir(char *redir)
{
	if (ft_equal_strs(redir, "|"))
		return (TOKEN_PIPE);
	if (ft_equal_strs(redir, "<"))
		return (TOKEN_REDIR_IN);
	if (ft_equal_strs(redir, ">"))
		return (TOKEN_REDIR_OUT);
	if (ft_equal_strs(redir, ">>"))
		return (TOKEN_REDIR_APP);
	if (ft_equal_strs(redir, "<<"))
		return (TOKEN_REDIR_HDOC);
	if (ft_equal_strs(redir, "&&"))
		return (TOKEN_AND);
	if (ft_equal_strs(redir, "||"))
		return (TOKEN_OR);
	return (TOKEN_UNKNOWN_REDIR);
}
