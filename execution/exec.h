#ifndef EXEC_H
# define EXEC_H



int built_in(t_command *cmd);
int cd_cmd(char *str);
int exec(t_command *cmd);
int echo_cmd(char **str); //Şimdilik char **str

# endif
