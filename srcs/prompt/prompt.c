/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:28:27 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/21 13:48:39 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_line(t_base *base, char *line)
{
	int	error;
	// implement (&& -- ||) and check number of commands
	ft_lexer_start(base, line);
	if (!errors_lexer(base))
	{
		error = format_redirections(base);
		if (error == -2 || error == -3)
		{
			base->exit_status = EXIT_FAILURE;
			update_for_next_line(base);
			return ;
		}
		else
		{
			if (base->pipe == 1)
			{
				printf("EXEC MULTIPLE PIPES\n");
				exec_pipes(base);
			}	
			else
				exec_single_cmd(base);
		}
		update_for_next_line(base);
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
	base->first_token = NULL;
	base->pipe = 0;
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
		{
			rl_insert_text("exit\n");
			rl_reset_line_state();
			break ;
		}
		line = ft_strtrim(rl, " \n\t");
		if (ft_strlen(line) > 0)
		{
			add_history(rl);
			exec_line(base, line);
		}
		ft_free_after_prompt(base, rl, line);
	}
}
