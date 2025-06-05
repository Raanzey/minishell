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
size_t		skip_word_count(const char *s, size_t i);
size_t		skip_word(const char *s, size_t i);
// size_t		quotes(char **tokens, const char *s, size_t *i, size_t k);
size_t		redirect(char **tokens, const char *s, size_t *i, size_t k);
int			handle_error(char **tokens);
char		**tokenizer(char const *s);
void	expand_args(t_command *cmd, int last_exit);
void	expand_redirections(t_command *cmd, int last_exit);

void		print_cmd(t_command *cmd);

#	endif