#ifndef PARS_H
# define PARS_H

typedef struct s_redirect {
	int type;          // 0: none, 1: >, 2: >>, 3: <, 4: <<
	char *filename; 
	struct s_redirect *next;
} t_redirect;

typedef struct s_command {
	char **av;         // ["ls", "-la", NULL]
	t_redirect *redir;   // I/O yönlendirmeleri
				// int [i] == 0 0 0 1 0 1
	int pipe;            // sonra pipe var mı? 0 veya 1
	struct s_command *next; // pipe varsa sonraki komut
} t_command;

t_command *parser(char **tokens);
size_t	skip_space(const char *s, size_t i);
size_t	skip_word_count(const char *s, size_t i);
size_t	skip_word(const char *s, size_t i);
size_t	quotes(char **tokens, const char *s, size_t *i, size_t k);
size_t	redirect(char **tokens, const char *s, size_t *i, size_t k);
char	**tokenizer(char const *s);

void	print_cmd(t_command *cmd); //! sil

# endif