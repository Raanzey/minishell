/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:13:07 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:13:07 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

# include "../structs.h"

t_command	*new_command(void);
int			is_redir(char *s);
t_redirect	*new_redirect(char *op, char *file);
void		add_redirect(t_command *cmd, t_redirect *r);
void		add_arg(t_command *cmd, char *word);
t_command	*parser(char **tokens);
int			skip_space(const char *s, int i);
int			redirect(char **tokens, const char *s, int *i, int k);
int			pre_parser_error(char **tokens, int i);
char		**tokenizer(char const *s);
char		*ft_strjoin_char(char *s, char c);
char		*expand_dollar(char *s, t_expand *info);
char		*expand(char *token, t_env *env, int exit_code, int i);
char		*exp_redir(char *token, t_env *env, int exit_code);
void		here_doc_no_expand(char **delimiter, size_t i, size_t j);
int			expand_args(t_command *cmd, t_env *env, int exit_code);
void		clean_empty_args_inplace(t_command *cmd);

#endif