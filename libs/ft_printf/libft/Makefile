NAME =		libft.a

SRCS = 		ft_strlen.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c ft_itoa.c ft_memset.c \
			ft_atoi.c ft_split.c ft_tablen.c ft_free_array.c ft_abs.c ft_toupper.c \
			ft_revstr.c ft_max.c ft_strncmp.c ft_substr.c ft_strjoin.c ft_strtrim.c \
			ft_isalnum.c ft_strdup.c ft_strlcpy.c ft_malloc.c ft_equal_strs.c \
			ft_strchr.c ft_strjoin_free.c ft_strnstr.c ft_strrchr.c
			
HEADERS =	libft.h

OBJS =		$(SRCS:.c=.o)
BONUS_OBJS =	$(BONUS:.c=.o)

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
				@ar rc $(NAME) $(OBJS)

%.o:		%.c
				@$(CC) $(CFLAGS) -o $@ -c $< -I $(HEADERS)

bonus:		$(OBJS) $(BONUS_OBJS)
				@ar rc $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
				@rm -f $(OBJS)

fclean:		clean
				@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
