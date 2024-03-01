/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:44:17 by sbelomet          #+#    #+#             */
/*   Updated: 2024/03/01 11:02:26 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_curdir(t_base *base)
{
	char	*res;
	int		i;

	if (ft_equal_strs(base->curdir, "/"))
		return (ft_strdup("/"));
	ft_revstr(base->curdir);
	i = 0;
	while (base->curdir[i])
	{
		if (base->curdir[i] == '/')
		{
			res = ft_substr(base->curdir, 0, i);
			if (!res)
				ft_error(base);
			ft_revstr(base->curdir);
			ft_revstr(res);
			return (res);
		}
		i++;
	}
	return (NULL);
}

char	*ft_format_prompt(t_base *base)
{
	char	*prompt;
	char	*tmp;
	char	*dir;

	dir = ft_get_curdir(base);
	tmp = ft_strjoin(dir, " $> ");
	free(dir);
	if (!tmp)
		ft_error(base);
	prompt = ft_strjoin("[MINISHELL] ", tmp);
	free(tmp);
	if (!prompt)
		ft_error(base);
	return (prompt);
}

void	ft_free_after_prompt(t_base *base, char *rl, char *line, char *prompt)
{
	ft_free_tokens(base->first_token);
	free_nodes(base);
	base->first_token = NULL;
	base->pipe = 0;
	free(rl);
	free(line);
	free(prompt);
}
