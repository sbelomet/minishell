/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:16:54 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/01 15:48:42 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_cmd(t_base *base, char *cmd)
{
	t_token	*res;
	char	*path;

	res = ft_new_token_node(TOKEN_UNKNOWN_CMD);
	if (!res)
		ft_error(base, "malloc()");
	ft_add_token_node(base, res);
	path = NULL;
	if (ft_isbuiltin(cmd))
		res->id = TOKEN_BUILTIN;
	else if (ft_isbin(base, cmd))
	{
		res->id = TOKEN_BIN;
		path = ft_get_cmdpath(base, cmd);
	}
	res->type = ft_new_cmd_node(res->id, path, cmd);
	if (!res->type)
		ft_error(base, "malloc()");
	t_cmd *test;

	test = (t_cmd *)res->type;
	printf("name: %s, id: %d, path: %s\n", test->name, test->id, test->path);
}

void	ft_add_cmd_arg(t_base *base, char *arg)
{
	t_token	*cmd_token;
	t_cmd	*cmd;
	t_arg	*arg_node;

	cmd_token = ft_last_token(base->first_token);
	cmd = (t_cmd *)cmd_token->type;
	arg_node = ft_new_arg_node(TOKEN_ARG, arg);
	if (!arg_node)
		ft_error(base, "malloc()");
	ft_add_arg_node(cmd, arg_node);
}

void	ft_tokenize_redir(t_base *base, char *redir)
{
	t_token	*res;

	res = ft_new_token_node(ft_get_redir(redir));
	if (!res)
		ft_error(base, "malloc()");
	ft_add_token_node(base, res);
	res->type = ft_new_redir_node(res->id, redir);
	if (!res->type)
		ft_error(base, "malloc()");
	t_redir *test;

	test = (t_redir *)res->type;
	printf("name: %s, id: %d\n", test->name, test->id);
}

void	ft_add_redir_file(t_base *base, char *file)
{
	//TODO
}

void	ft_tokenize(t_base *base, char *val, int id)
{
	printf("id: %d\n", id);
	if (id == TOKEN_CMD)
	{
		ft_tokenize_cmd(base, val);
	}
	else if (id == TOKEN_ARG)
	{
		ft_add_cmd_arg(base, val);
	}
	else if (id == TOKEN_REDIR)
	{
		ft_tokenize_redir(base, val);
	}
	else if (id == TOKEN_FILE)
	{
		ft_add_redir_file(base, val);
	}
}