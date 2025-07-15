NAME 		= minishell
CC		= cc
CFLAGS 		= -Wall -Wextra -Werror
LIBFLAGS	= -lreadline
SRCS		= main.c execution/exec.c execution/exec_utils.c \
			execution/built_in/built_in.c execution/built_in/built_in_utils.c \
			execution/built_in/env_fonc_utils.c execution/built_in/env_fonc.c \
			parser/token.c parser/token_utils.c parser/error_handle.c \
			parser/pars.c parser/pars_utils.c \
			parser/expansion.c parser/expansion_utils.c parser/expansion_extra_utils.c\

LIBFT		= Libft/libft.a
DIR_LIBFT	= Libft

all: $(NAME)

$(NAME): $(SRCS)
	make -s  -C $(DIR_LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(LIBFLAGS) -o $(NAME)

clean:
	make -s -C $(DIR_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -s -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re 