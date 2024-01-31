/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:24:08 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/31 13:57:20 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltin(t_base *base, char *cmd)
{
	int	i;

	i = 0;
	while (base->builtins[i])
	{
		if (ft_equal_strs(base->builtins[i], cmd))
			return (1);
		i++;
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
	return (res);
}
