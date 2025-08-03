NAME 		= minishell
CC		= cc
CFLAGS 		= -Wall -Wextra -Werror
LIBFLAGS	= -lreadline
SRCS		= main.c utils.c signal.c execution/exec.c execution/exec_utils.c \
			execution/heredoc.c execution/heredoc_utils.c \
			execution/built_in/built_in.c execution/built_in/built_in_parent.c \
			execution/built_in/env_exp_func/env.c execution/built_in/env_exp_func/exp.c \
			execution/built_in/env_exp_func/exp_utils.c \
			parser/token.c parser/token_utils.c parser/error_handle.c \
			parser/pars.c parser/pars_utils.c parser/clean.c \
			parser/expansion.c parser/expansion_utils.c \
			

LIBMINI		= libmini/libmini.a
COLLECTOR	= collector/collector.a
DIR_LIBMINI	= libmini
DIR_COLLECTOR	= collector

all: $(NAME)

$(NAME): $(SRCS)
	make -s  -C $(DIR_LIBMINI)
	make -s  -C $(DIR_COLLECTOR)
	$(CC) $(CFLAGS) $(SRCS) $(COLLECTOR) $(LIBMINI) $(LIBFLAGS) -o $(NAME)

clean:
	make -s -C $(DIR_LIBMINI) clean
	make -s -C $(DIR_COLLECTOR) clean

fclean: clean
	rm -f $(NAME)
	make -s -C $(DIR_LIBMINI) fclean
	make -s -C $(DIR_COLLECTOR) fclean

re: fclean all
	
leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell

.PHONY: all clean fclean re 