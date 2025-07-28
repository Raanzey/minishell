/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:24:18 by musisman          #+#    #+#             */
/*   Updated: 2025/05/29 17:24:18 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

# include "structs.h"

t_command	*new_command(void);
int			is_redir(char *s);
t_redirect	*create_redirect(char *op, char *file);
void		add_redirect(t_command *cmd, t_redirect *r);
void		add_arg(t_command *cmd, char *word);
t_command	*parser(char **tokens);
int		skip_space(const char *s, int i);
int		redirect(char **tokens, const char *s, int *i, int k);
int			pre_parser_error(char **tokens, int i);
int			handle_error(t_command *cmd);
char		**tokenizer(char const *s);
char		*ft_strjoin_char(char *s, char c);
char		*append_substring(char *res, const char *src, int one, int end);
char		*expand_dollar(char *s, t_expand *info);
char		*expand_token(const char *token, t_env *env_list, int exit_code);
void		expand_and_replace(char **str, t_env *env_list, int last_exit);
void		here_doc_no_expand(char **target, size_t i, size_t j);
int			expand_args(t_command *cmd, t_env *env_list, int exit_code);
void		clean_empty_args_inplace(t_command *cmd);

#endif