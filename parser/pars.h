#ifndef PARS_H
# define PARS_H

typedef struct s_redirect {
	int type;          // 0: none, 1: >, 2: >>, 3: <, 4: <<
	char *filename;
	struct s_redirect *next;
} t_redirect;

typedef struct s_command {
	char **argv;         // ["ls", "-la", NULL]
	t_redirect *redir;   // I/O yönlendirmeleri
	int pipe;            // sonra pipe var mı? 0 veya 1
	struct s_command *next; // pipe varsa sonraki komut
} t_command;

void parser(char *input);

# endif