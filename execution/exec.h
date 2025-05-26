#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"

int built_in(t_command *cmd);
int echo_cmd(char **str); //Şimdilik char **str

# endif
