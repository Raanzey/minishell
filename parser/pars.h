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

typedef struct s_redirect {
	int					type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command {
	char				**av;
	t_redirect			*redir;
	struct s_command	*next;
}	t_command;

t_command	*new_command(void);
int			is_redir(char *s);
t_redirect	*create_redirect(char *op, char *file);
void		add_redirect(t_command *cmd, t_redirect *r);
void		add_arg(t_command *cmd, char *word);
t_command	*parser(char **tokens);
size_t		skip_space(const char *s, size_t i);
// size_t		quotes(char **tokens, const char *s, size_t *i, size_t k);
size_t		redirect(char **tokens, const char *s, size_t *i, size_t k);
int			handle_error(char **tokens);
char		**tokenizer(char const *s);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin_char(char *s, char c);
char		*append_substring(char *res, const char *src, int one, int end);
char		*expand_dollar(const char *s, int last_exit);
char		*expand_token(const char *token, int last_exit);
void		expand_and_replace(char **str, int last_exit);
int			expand_args(t_command *cmd, int last_exit, int i);

void		print_cmd(t_command *cmd); //!sil

#	endif