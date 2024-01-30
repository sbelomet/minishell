/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:07:14 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/26 15:36:08 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pwd(void)
{
    char    *path;

    path = get_current_path();
    ft_putstr_fd(path, STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}