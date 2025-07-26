NAME 		= minishell
CC		= cc
CFLAGS 		= -Wall -Wextra -Werror
LIBFLAGS	= -lreadline
SRCS		= main.c utils.c execution/exec.c execution/exec_utils.c execution/heredoc.c \
			execution/built_in/built_in.c execution/built_in/built_in_parent.c \
			execution/built_in/env_exp_func/env.c execution/built_in/env_exp_func/exp.c execution/built_in/env_exp_func/exp_utils.c \
			parser/token.c parser/token_utils.c parser/error_handle.c \
			parser/pars.c parser/pars_utils.c parser/clean.c \
			parser/expansion.c parser/expansion_utils.c parser/expansion_extra_utils.c \
			

LIBFT		= Libft/libft.a
COLLECTOR	= collector/collector.a
DIR_LIBFT	= Libft
DIR_COLLECTOR	= collector

all: $(NAME)

$(NAME): $(SRCS)
	make -s  -C $(DIR_LIBFT)
	make -s  -C $(DIR_COLLECTOR)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(COLLECTOR) $(LIBFLAGS) -o $(NAME)

clean:
	make -s -C $(DIR_LIBFT) clean
	make -s -C $(DIR_COLLECTOR) clean

fclean: clean
	rm -f $(NAME)
	make -s -C $(DIR_LIBFT) fclean
	make -s -C $(DIR_COLLECTOR) fclean

re: fclean all

run:
	@./${NAME}
	
leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell

.PHONY: all clean fclean re 