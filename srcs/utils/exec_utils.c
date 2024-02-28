/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:36:10 by lgosselk          #+#    #+#             */
/*   Updated: 2024/02/28 15:31:33 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_streams(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
}

int	get_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
	{
		return (WEXITSTATUS(exit_status));
	}
	else if (WIFSIGNALED(exit_status))
	{
		return (WTERMSIG(exit_status) + 128);
	}
	return (1);
}

char	*ft_triple_strjoin(char const *s1, char const *s2,
		char const *s3)
{
	int		i;
	char	*res;
	int		len_s1;
	int		len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = (char *)malloc((len_s1 + len_s2 + ft_strlen(s3) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	i = -1;
	while (s2[++i])
		res[len_s1 + i] = s2[i];
	i = -1;
	while (s3[++i])
		res[len_s1 + len_s2 + i] = s3[i];
	res[len_s1 + len_s2 + i] = '\0';
	return (res);
}

char	**get_args_tab(t_arg *args, char *path)
{
	int		i;
	char	**tab;
	char	*temp;
	char	*str_args;

	str_args = ft_strdup(path);
	i = 1;
	while (args)
	{
		temp = str_args;
		str_args = ft_triple_strjoin(temp, " ", args->name);
		free(temp);
		temp = NULL;
		args = args->next;
		i++;
	}
	tab = ft_split(str_args, ' ');
	tab[i] = NULL;
	free(str_args);
	if (!tab)
		return (NULL);
	return (tab);
}
