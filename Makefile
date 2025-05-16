NAME 		= minishell
CC			= cc
CFLAGS 		= -Wall -Wextra -Werror -lreadline
SRCS		= main.c execution/exec.c parser/pars.c\

LIBFT		= Libft/libft.a
DIR_LIBFT	= Libft

all: $(NAME)

$(NAME): $(SRCS)
	make -s -C $(DIR_LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	make -s -C $(DIR_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -s -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re 