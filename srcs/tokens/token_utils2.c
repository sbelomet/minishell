/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:09:38 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/20 10:10:29 by sbelomet         ###   ########.fr       */
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
