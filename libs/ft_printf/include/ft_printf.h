/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:26:28 by sbelomet          #+#    #+#             */
/*   Updated: 2024/02/08 11:47:36 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

# include "../libft/libft.h"

int		ft_printf(int fd, const char *format, ...);
int		ft_printstr(char *s, int fd);
int		ft_printptr(unsigned long long a, int fd);
int		ft_printhex(unsigned long long a, char isupper, int fd);
char	ft_converthex(int a, char isupper);
char	*ft_uitoa(unsigned int n);
int		ft_printformat(va_list args, char format, int fd);

#endif
