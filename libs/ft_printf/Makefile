# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 13:12:12 by sbelomet          #+#    #+#              #
#    Updated: 2023/11/22 16:07:27 by sbelomet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables

NAME		=	libftprintf.a
HEADERS		=	include
SRC_DIR		=	src/
OBJ_DIR		=	obj/
LIBFT		=	libft
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I

#Sources

SRC_RAW		=	ft_printf ft_printformat ft_printstr ft_printptr ft_printhex ft_converthex ft_uitoa

SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_RAW)))
OBJS		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_RAW)))

###

OBJF		=	.cache_exists

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -C $(LIBFT) all
				@cp $(LIBFT)/libft.a $(NAME)
				@ar rc $(NAME) $(OBJS)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJF)
				@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(OBJF):
				@mkdir -p $(OBJ_DIR)

clean:
				@rm -rf $(OBJ_DIR)
				@make -C $(LIBFT) clean

fclean:			clean
				@make -C $(LIBFT) fclean
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re libft
