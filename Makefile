NAME = pipex

SRCS = free.c ft_split.c handle_error.c \
		path.c pipex_utils.c pipex.c	\
		utils.c

SRCS_BONUS =	free_bonus.c ft_split_bonus.c handle_error_bonus.c \
		path_bonus.c pipex_utils_bonus.c pipex_bonus.c	\
		utils_bonus.c utils2_bonus.c here_doc.c \

OBJS  = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc
CFLAG = -Wall -Wextra -Werror -Wunreachable-code
# CFLAG = -g
all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAG) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
		$(CC) $(CFLAG) $(OBJS_BONUS) -o $(NAME)

%.o: %.c $(HEADER_FILE)
		$(CC) -c $(CFLAG) $^ -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
