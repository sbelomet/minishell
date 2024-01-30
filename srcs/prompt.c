/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:28:27 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/30 11:27:27 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_vars(t_base base)
{
	while (base.first_var)
	{
		ft_printf("NAME: %s\nVALUE: %s\n",
			base.first_var->name, base.first_var->value);
		base.first_var = base.first_var->next;
	}
}

char	*ft_format_prompt(t_base *base)
{
	char	*prompt;
	char	*tmp;

	tmp = ft_strjoin(base->curdir, " $> ");
	if (!tmp)
		ft_error(base, "malloc()");
	prompt = ft_strjoin("[MINISHELL] ", tmp);
	if (!prompt)
		ft_error(base, "malloc()");
	free(tmp);
	return (prompt);
}

void	ft_prompt(t_base *base)
{
	char	*rl;
	char	*prompt;
	char	*line;

	while (1)
	{
		prompt = ft_format_prompt(base);
		rl = readline(prompt);
		free(prompt);
		if (!rl)
			break ;
		line = ft_strtrim(rl, " \n\t");
		if (ft_strlen(line) > 0)
		{
			add_history(rl);
			if (ft_strncmp("print", line, 5) == 0)
				ft_print_vars(*base);
			else
				ft_lexer_start(base, line);
		}
		free(rl);
		free(line);
	}
}
