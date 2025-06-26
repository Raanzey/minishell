#ifndef EXEC_H
# define EXEC_H

typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
} t_env;

extern t_env *g_env_list;

int built_in(t_command *cmd);
int is_parent_builtin(t_command *cmd);
int exec(t_command *cmd, char **env);
int echo_cmd(char **str);
int cd_cmd(char *str);
int pwd_cmd();
int env_cmd(t_env *env);
int export_cmd(char **av, t_env *env);
int unset_cmd(char **av);
char *ft_path(void);
void	handle_heredoc(const char *delimiter);
void print_export(t_env *env);
void add_or_update_env(t_env *env, char *eq, char *av);
void export_key_only(t_env *env, const char *key);
void unset_var(t_env **env, const char *key);
t_env *init_env(char **env);
t_env *find_env(t_env *env, const char *key);

# endif
