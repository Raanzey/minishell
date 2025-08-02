SRCS = ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isdigit.c \
        ft_itoa.c ft_memcpy.c ft_split.c ft_strchr.c \
        ft_strcmp.c ft_strdup.c ft_strjoin_char.c ft_strjoin.c \
        ft_strlen.c ft_strncmp.c ft_substr.c \

OBJS = $(SRCS:.c=.o)

NAME = libmini.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
