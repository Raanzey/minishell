CC = cc
RM = rm -rf
AR = ar rc

CFLAGS = -Wall -Werror -Wextra

SRCS = utils.c collector.c

OBJS = $(SRCS:.c=.o)

NAME = collector.a

all: dir $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re dir