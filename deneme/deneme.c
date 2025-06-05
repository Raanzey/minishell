#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
# include <readline/history.h>

typedef struct s_redirect {
	char				*filename;
	int					type;
	int					expand;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command {
	char			**av;
	t_redirect		*redir;
	struct s_command *next;
}	t_command;

/* === Libft gereği === */
char	*ft_strdup(const char *s) {
	size_t len = strlen(s);
	char *copy = malloc(len + 1);
	return (copy ? strcpy(copy, s) : NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n) {
	while (n && *s1 && *s2 && *s1 == *s2) n--, s1++, s2++;
	return (n ? *(unsigned char *)s1 - *(unsigned char *)s2 : 0);
}

void	*ft_calloc(size_t nmemb, size_t size) {
	void *p = malloc(nmemb * size);
	if (p)
		memset(p, 0, nmemb * size);
	return p;
}

char	*ft_substr(const char *s, unsigned int start, size_t len) {
	size_t slen = strlen(s);
	if (start >= slen) return strdup("");
	if (len > slen - start) len = slen - start;
	char *sub = malloc(len + 1);
	if (!sub) return NULL;
	strncpy(sub, s + start, len);
	sub[len] = '\0';
	return sub;
}

int	error(const char *msg) {
	fprintf(stderr, "-bash: %s\n", msg);
	return (1);
}

/* === Tokenizer === */
int	is_space(char c) {
	return (c == ' ' || (c >= 9 && c <= 13));
}

size_t	skip_space(const char *s, size_t i) {
	while (s[i] && is_space(s[i])) i++;
	return i;
}

int	quotes_control(const char *s, size_t *i) {
	char q = s[(*i)++];
	while (s[*i] && s[*i] != q) (*i)++;
	return (s[*i] == q) ? (*i)++, 1 : 0;
}

size_t	token_count(const char *s) {
	size_t i = 0, count = 0;
	while (s[i]) {
		i = skip_space(s, i);
		if (!s[i]) break;
		if (s[i] == '<' || s[i] == '>' || s[i] == '|') {
			if (s[i + 1] == s[i]) i++;
			i++;
		} else {
			while (s[i] && !is_space(s[i]) && s[i] != '<' && s[i] != '>' && s[i] != '|') {
				if (s[i] == '\'' || s[i] == '"') {
					if (!quotes_control(s, &i)) return (0);
				} else i++;
			}
		}
		count++;
	}
	return count;
}

char	*ft_strndup(const char *s, size_t n) {
	char *p = malloc(n + 1);
	if (!p) return NULL;
	strncpy(p, s, n);
	p[n] = 0;
	return p;
}

size_t	handle_word(char **tokens, const char *s, size_t *i, size_t k) {
	size_t start = *i;
	while (s[*i] && !is_space(s[*i]) && s[*i] != '<' && s[*i] != '>' && s[*i] != '|') {
		if (s[*i] == '"' || s[*i] == '\'') {
			if (!quotes_control(s, i)) return 0;
		} else (*i)++;
	}
	tokens[k] = ft_strndup(s + start, *i - start);
	return (k + 1);
}

size_t	redirect(char **tokens, const char *s, size_t *i, size_t k) {
	if ((s[*i] == '<' && s[*i + 1] == '<') || (s[*i] == '>' && s[*i + 1] == '>')) {
		tokens[k] = ft_strndup(s + *i, 2);
		*i += 2;
	} else {
		tokens[k] = ft_strndup(s + *i, 1);
		(*i)++;
	}
	return (k + 1);
}

char	**tokenizer(const char *s) {
	size_t i = 0, k = 0, total = token_count(s);
	char **tokens = ft_calloc(total + 1, sizeof(char *));
	if (!tokens) return NULL;
	while (s[i]) {
		i = skip_space(s, i);
		if (!s[i]) break;
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			k = redirect(tokens, s, &i, k);
		else
			k = handle_word(tokens, s, &i, k);
	}
	return tokens;
}

/* === Parser === */
int	is_redir(char *s) {
	return (!strcmp(s, "<") || !strcmp(s, "<<") || !strcmp(s, ">") || !strcmp(s, ">>"));
}

t_redirect	*create_redirect(char *op, char *file) {
	t_redirect *r = malloc(sizeof(t_redirect));
	if (!r) return NULL;
	r->filename = strdup(file);
	r->next = NULL;
	r->expand = 1;
	if (!strcmp(op, "<<")) {
		r->type = 4;
		if (file[0] == '\'' && file[strlen(file) - 1] == '\'')
			r->expand = 0;
	} else if (!strcmp(op, ">>"))
		r->type = 2;
	else if (!strcmp(op, "<"))
		r->type = 3;
	else
		r->type = 1;
	return r;
}

void	add_redirect(t_command *cmd, t_redirect *r) {
	t_redirect *cur = cmd->redir;
	if (!cur)
		cmd->redir = r;
	else {
		while (cur->next) cur = cur->next;
		cur->next = r;
	}
}

void	add_arg(t_command *cmd, char *w) {
	int i = 0;
	while (cmd->av && cmd->av[i]) i++;
	char **new = ft_calloc(i + 2, sizeof(char *));
	for (int j = 0; j < i; j++) new[j] = cmd->av[j];
	new[i] = strdup(w);
	free(cmd->av);
	cmd->av = new;
}

t_command	*new_command(void) {
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd) return NULL;
	cmd->av = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return cmd;
}

t_command	*parser(char **tokens) {
	t_command *first = NULL, *cur = NULL, *cmd;
	size_t i = 0;
	while (tokens[i]) {
		cmd = new_command();
		if (!first) first = cmd;
		else cur->next = cmd;
		cur = cmd;
		while (tokens[i] && strcmp(tokens[i], "|")) {
			if (is_redir(tokens[i]) && tokens[i + 1]) {
				add_redirect(cmd, create_redirect(tokens[i], tokens[i + 1]));
				i += 2;
			} else
				add_arg(cmd, tokens[i++]);
		}
		if (tokens[i] && !strcmp(tokens[i], "|")) i++;
	}
	return first;
}

/* === Expansion örneği === */
char	*expand_token(const char *s, int last_exit) {
	if (!strcmp(s, "$?")) return ft_strdup("0");
	if (!strncmp(s, "$", 1)) {
		char *val = getenv(s + 1);
		return val ? ft_strdup(val) : ft_strdup("");
	}
	return ft_strdup(s);
}

void	expand_args(t_command *cmd, int last_exit) {
	int i;
	char *tmp;

	while (cmd) {
		for (i = 0; cmd->av && cmd->av[i]; i++) {
			tmp = expand_token(cmd->av[i], last_exit);
			free(cmd->av[i]);
			cmd->av[i] = tmp;
		}
		cmd = cmd->next;
	}
}

/* === Test main() === */
void	print_cmd(t_command *cmd) {
	int i = 0, num = 1;
	t_redirect *r;
	while (cmd) {
		printf("=== COMMAND %d ===\n", num++);
		printf("ARGS:\n");
		for (i = 0; cmd->av && cmd->av[i]; i++)
			printf("av[%d]: %s\n", i, cmd->av[i]);
		printf("REDIRS:\n");
		for (r = cmd->redir; r; r = r->next)
			printf("type: %d, file: %s (expand=%d)\n", r->type, r->filename, r->expand);
		cmd = cmd->next;
	}
}

int	main(void) {
	char *input;
	char **tokens;
	t_command *cmd;

	while (1) {
		input = readline("minishell~ ");
		if (!input) break;
		if (!strncmp(input, "exit", 4)) break;
		tokens = tokenizer(input);
		if (!tokens) continue;
		cmd = parser(tokens);
		expand_args(cmd, 0);
		print_cmd(cmd);
		free(input);
	}
	return 0;
}
