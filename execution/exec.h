#ifndef EXEC_H
# define EXEC_H

typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
} t_env;

int built_in(t_command *cmd, t_env **env_list);
int is_parent_builtin(t_command *cmd);
int exec(t_command *cmd, t_env **env_list);
int echo_cmd(char **str);
int cd_cmd(t_command *cmd);
int pwd_cmd();
int env_cmd(t_env *env);
int export_cmd(char **av, t_env **env, t_command *cmd);
// int export_cmd(char **av, t_env **env);
int unset_cmd(t_command *cmd, t_env **env_list);
char *ft_path(t_env *env);
void handle_heredocs(t_redirect *redir, int has_cmd);
void print_export(t_env *env);
void add_or_update_env(t_env **env, char *eq, char *av);
void export_key_only(t_env **env, const char *key);
void unset_var(t_env **env, const char *key);
void insert_sorted_env(t_env **env, char *key, char *value);
void update_env(t_env *node, const char *value);
t_env *init_env(char **env, int i);
t_env *find_env(t_env *env, const char *key);

void	setup_signals_main();
void	sigint_handler(int sig);
void	handle_sigint_exec(int sig);
void	discard_signals();
int is_numeric(const char *str);
int	exit_cmd(char **av);

# endif
