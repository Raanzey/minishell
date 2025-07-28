/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:02:46 by musisman          #+#    #+#             */
/*   Updated: 2025/07/28 22:54:45 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../parser/structs.h"

int		built_in(t_command *cmd, t_env **env_list);
int		is_parent_builtin(t_command *cmd);
int		exec(t_command *cmd, t_env **env_list);
int		echo_cmd(char **str);
int		cd_cmd(t_command *cmd, t_env *env_list);
int		pwd_cmd(void);
int		env_cmd(t_env *env);
int		export_cmd(char **av, t_env **env, t_command *cmd);
int		unset_cmd(t_command *cmd, t_env **env_list);
int		is_valid_identifier(char *str);
void	handle_heredocs(t_redirect *redir, int has_cmd, int heredoc_fd);
int		has_output_redir(t_redirect *redir);
int		open_redir_fd(t_redirect *redir);
char	*ft_path(t_env *env);
char	*get_env_value(t_env *env, const char *key);
char	*find_path(char *cmd, t_env *env_list);
char	**convert_env_to_array(t_env *env, int count, int i, char *joined);
char	*handle_path(t_command *cmd, t_env **env_list);
void	setup_pipe_or_die(t_command *cmd, int pipe_fd[2]);
void	dup_redir_fd(t_redirect *redir, int fd);
void	child_redirect(t_command *cmd, int prev_fd, int pipe_fd[2]);
void	print_export(t_env *env);
void	add_or_update_env(t_env **env, char *eq, char *av);
void	export_key_only(t_env **env, const char *key);
void	unset_var(t_env **env, const char *key);
void	update_env(t_env *node, const char *value);
void	handle_redirections(t_command *cmd);
t_env	*init_env(char **env, int i);
t_env	*create_env_node(char *key, char *value, t_env *next);
t_env	*find_env(t_env *env, const char *key);

void	setup_signals(void);
void	discard_signals(void);
int		is_numeric(const char *str);
int		exit_cmd(char **av);

#endif
