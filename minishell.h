#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <parser/pars.h>


# include "Libft/libft.h"

# define ERR_ARG "Please no argument\n" // .minishell dasda hata durumu
# define ERR_EXIT "numeric argument required\n" // exit dsda hata durumu

int error(char *err);

# endif