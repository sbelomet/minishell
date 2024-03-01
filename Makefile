# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 12:53:58 by sbelomet          #+#    #+#              #
#    Updated: 2024/03/01 09:54:25 by lgosselk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -fsanitize=address -g3

# Variables

NAME		=	minishell
HEADERS		=	-I includes -I $(HOME)/.brew/Cellar/readline/8.2.7/include
SRC_DIR		=	srcs/
OBJ_DIR		=	objs/
LIBFTPRINTF =   libs/ft_printf/libftprintf.a
LIBRL		=	-L $(HOME)/.brew/Cellar/readline/8.2.7/lib
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LEAKS		=	leaks --atExit -- 

D_MAIN		=	main_utils/
D_PROMPT	=	prompt/
D_LEXER		=	lexer/
D_TOKEN		=	tokens/
D_VARS		=	variables/
D_ERRORS	=	errors/
D_FORMAT	=	formatting/
D_CHECKS	=	checkers/
D_BUILTIN	=	builtins/
D_EXEC		=	exec/
D_GETTERS	=	getters/
D_UPDATE	=	updates/
D_UTILS		=	utils/

# Colors

RED 		=	\033[1;91m
YELLOW		=	\033[1;93m
GREEN		=	\033[1;92m
BLUE		=	\033[1;94m
PURPLE		=	\033[1;95m
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
MAGENTA		=	\033[0;95m
CYAN		=	\033[1;96m
WHITE		=	\033[0;97m
RAINBOW		=	$(RED)-$(YELLOW)-$(GREEN)-$(CYAN)-$(BLUE)-$(PURPLE)-

# Sources

F_MAIN		=	main base_init error_utils1 signals_utils1 signals_utils2 shell_level
F_PROMPT	=	prompt freeing_tokens prompt_cmd prompt_format
F_LEXER		=	lexer lexer_utils1 lexer_utils2 lexer_utils3
F_TOKEN		=	tokens token_utils1 token_utils2 token_list_utils1 \
				args_list_utils1 cmd_list_utils1 redir_list_utils1
F_VARS		=	variables_utils1 variables_utils2 variables_list_utils1
F_ERRORS	=	lexer_errors redirect_errors
F_FORMAT	=	formatting_redirections formatting_redirections_2
F_CHECKS	=	check_args check_builtin check_command check_token check_token_2
F_BUILTIN	=	cd echo env exec_builtin exit export pwd unset export_2 export_3
F_EXEC		=	exec_pipes here_doc exec_single_cmd exec_pipes_2
F_GETTERS	=	get_args get_class get_env get_token_2 get_token get_token_3
F_UPDATE	=	update_env update_last_arg updates
F_UTILS		=	exec_utils exec_utils_2

FILES		=	$(addprefix $(D_MAIN), $(F_MAIN)) \
				$(addprefix $(D_PROMPT), $(F_PROMPT)) \
				$(addprefix $(D_LEXER), $(F_LEXER)) \
				$(addprefix $(D_TOKEN), $(F_TOKEN)) \
				$(addprefix $(D_VARS), $(F_VARS)) \
				$(addprefix $(D_ERRORS), $(F_ERRORS)) \
				$(addprefix $(D_FORMAT), $(F_FORMAT)) \
				$(addprefix $(D_CHECKS), $(F_CHECKS)) \
				$(addprefix $(D_BUILTIN), $(F_BUILTIN)) \
				$(addprefix $(D_EXEC), $(F_EXEC)) \
				$(addprefix $(D_GETTERS), $(F_GETTERS)) \
				$(addprefix $(D_UPDATE), $(F_UPDATE)) \
				$(addprefix $(D_UTILS), $(F_UTILS))

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# Commands

all:			$(OBJ_DIR) $(NAME)

$(NAME):		$(OBJ)
					@echo "$(RAINBOW)$(RAINBOW)$(RAINBOW)$(DEF_COLOR)"
					@make -C libs/ft_printf
					$(CC) $(CFLAGS) $(OBJ) $(LIBFTPRINTF) $(LIBRL) -lreadline -o $(NAME)
					@echo ""
					@echo "$(GREEN)$(NAME) est compilé !$(DEF_COLOR)🥶🥶🥶"
					@echo "$(RAINBOW)$(RAINBOW)$(RAINBOW)$(DEF_COLOR)"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c	
					@echo "$(YELLOW)$< est dans le four...$(DEF_COLOR)🥵🥵🥵"
					@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(D_MAIN)
					@mkdir -p $(OBJ_DIR)$(D_PROMPT)
					@mkdir -p $(OBJ_DIR)$(D_LEXER)
					@mkdir -p $(OBJ_DIR)$(D_TOKEN)
					@mkdir -p $(OBJ_DIR)$(D_VARS)
					@mkdir -p $(OBJ_DIR)$(D_ERRORS)
					@mkdir -p $(OBJ_DIR)$(D_FORMAT)
					@mkdir -p $(OBJ_DIR)$(D_CHECKS)
					@mkdir -p $(OBJ_DIR)$(D_BUILTIN)
					@mkdir -p $(OBJ_DIR)$(D_EXEC)
					@mkdir -p $(OBJ_DIR)$(D_GETTERS)
					@mkdir -p $(OBJ_DIR)$(D_UPDATE)
					@mkdir -p $(OBJ_DIR)$(D_UTILS)

clean:
					@make clean -C libs/ft_printf
					@rm -rf $(OBJ_DIR)
					@echo "$(RAINBOW)$(RAINBOW)$(RAINBOW)$(DEF_COLOR)"
					@echo "$(BLUE)à la poubelle les .o$(DEF_COLOR)🤓🤓🤓"

fclean:			clean
					@make fclean -C libs/ft_printf
					@rm -rf $(NAME)
					@echo "$(CYAN)à la poubelle l'exec$(DEF_COLOR)🤤🤤🤤"

re:				fclean all

run:			re
					$(LEAKS)./$(NAME)

.PHONY:			all clean fclean re run
