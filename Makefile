NAME = pipex

SRCS = free.c ft_split.c handle_error.c \
		path.c pipex_utils.c pipex.c	\
		utils.c

BONUS =	free_bonus.c ft_split_bonus.c handle_error_bonus.c \
		path_bonus.c pipex_utils_bonus.c pipex_bonus.c	\
		utils_bonus.c

OBJS  = $(SRCS:.c=.o)



CC = cc
CFLAG = -Wall -Wextra -Werror -Wunreachable-code
CFLAG = -g
all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAG) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER_FILE)
		$(CC) -c $(CFLAG) $^ -o $@

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

norm :
	norminette

valgrind : $(NAME)
	valgrind --track-fds=yes --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)
re: fclean all

.PHONY: all clean fclean re
