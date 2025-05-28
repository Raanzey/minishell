#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "Libft/libft.h"
# include "parser/pars.h"
# include "execution/exec.h"

# define ERR_ARG "Please no argument\n" // .minishell dasda hata durumu
# define ERR_EXIT "numeric argument required\n" // exit dsda hata durumu

int error(char *err);

# endif