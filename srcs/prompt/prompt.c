/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:28:27 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/14 14:26:36 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_line(t_base *base, char *line)
{
	// implement (&& -- ||) and check number of commands
	ft_lexer_start(base, line);
	if (!errors_lexer(base))
	{
		if (format_redirections(base) == -2)
			base->exit_status = EXIT_FAILURE; // signal heredoc
		else
		{
			if (base->pipe == 1)
				exec_pipes(base);
			else
				exec_single_cmd(base);
		}
	}
}

char	*ft_get_curdir(t_base *base)
{
	char	*res;
	int		i;

	ft_revstr(base->curdir);
	i = 0;
	while (base->curdir[i])
	{
		if (base->curdir[i] == '/')
		{
			res = ft_substr(base->curdir, 0, i);
			if (!res)
				ft_error(base, "malloc()");
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
	if (!tmp)
		ft_error(base, "malloc()");
	prompt = ft_strjoin("[MINISHELL] ", tmp);
	if (!prompt)
		ft_error(base, "malloc()");
	free(tmp);
	free(dir);
	return (prompt);
}

void	ft_free_after_prompt(t_base *base, char *rl, char *line)
{
	ft_free_tokens(base->first_token);
	ft_malloc_clear(&base->alloc);
	base->first_token = NULL;
	free(rl);
	free(line);
}

void	ft_prompt(t_base *base)
{
	char	*rl;
	char	*prompt;
	char	*line;

	while (1)
	{
		ft_signals();
		prompt = ft_format_prompt(base);
		rl = readline(prompt);
		free(prompt);
		if (!rl)
			break ;
		line = ft_strtrim(rl, " \n\t");
		if (ft_strlen(line) > 0)
		{
			add_history(rl);
			exec_line(base, line);
		}
		ft_free_after_prompt(base, rl, line);
	}
}
