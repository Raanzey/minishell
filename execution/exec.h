#ifndef EXEC_H
# define EXEC_H



int built_in(t_command *cmd);
int exec(t_command *cmd, char **env);
int echo_cmd(char **str);
int cd_cmd(char *str);
int pwd_cmd(char *str);

# endif
