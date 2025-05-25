#include "../minishell.h"

size_t	ft_word(t_command *cmd, char *token)
{
	int i = 0;

	while (cmd->av && cmd->av[i])
		i++;

	char **new_argv = ft_calloc(i + 2, sizeof(char *));
	if (!new_argv)
		return (0);
	for (int j = 0; j < i; j++)
		new_argv[j] = cmd->av[j];
	new_argv[i] = ft_strdup(token);
	new_argv[i + 1] = NULL;
	free(cmd->av);
	cmd->av = new_argv;
	return (1);
}

size_t	ft_redirect(t_command *cmd, char **tokens, size_t i)
{
	t_redirect *redir;

	if (!tokens[i + 1])
	{
		printf("syntax error: missing filename after redirection\n");
		return (0); // ya da hata kodu döndür
	}

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (0);
	if (ft_strncmp(tokens[i], "<<", 3) == 0)
		redir->type = 4;
	else if (ft_strncmp(tokens[i], ">>", 3) == 0)
		redir->type = 2;
	else if (ft_strncmp(tokens[i], "<", 2) == 0)
		redir->type = 3;
	else if (ft_strncmp(tokens[i], ">", 2) == 0)
		redir->type = 1;
	else
	{
		free(redir);
		return (0);
	}

	redir->filename = ft_strdup(tokens[i + 1]);
	redir->next = NULL;

	// Redir zincirine ekle
	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		t_redirect *tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	return (1); // kaç token yediğini belirtmek için
}

void	free_command(t_command *cmd)
{
	int i = 0;

	if (!cmd)
		return;
	if (cmd->av)
	{
		while (cmd->av[i])
			free(cmd->av[i++]);
		free(cmd->av);
	}
	t_redirect *r = cmd->redir;
	while (r)
	{
		t_redirect *tmp = r;
		r = r->next;
		free(tmp->filename);
		free(tmp);
	}
	free(cmd);
}

t_command	*parser(char *input)
{
	t_command	*cmd;
	char		**tokens;
	size_t		i;
	int			consumed;

	tokens = tokenizer(input);
	if (!tokens)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
			break ; // pipe desteği için ileride yeni t_command oluşturulacak

		if (ft_strncmp(tokens[i], "<", 2) == 0
			|| ft_strncmp(tokens[i], ">", 2) == 0
			|| ft_strncmp(tokens[i], "<<", 3) == 0
			|| ft_strncmp(tokens[i], ">>", 3) == 0)
		{
			consumed = ft_redirect(cmd, tokens, i);
			if (consumed == 0)
			{
				printf("Parsing error: missing filename after redirection\n");
				// Burada sadece parser kısmı olduğundan input'u main'de free'le
				free_command(cmd); // bunu yazmadıysan beraber yazarız
				return (NULL);
			}
			i += consumed;
		}
		else
		{
			ft_word(cmd, tokens[i]);
			i++;
		}
	}
	return (cmd);
}


void	print_cmd(t_command *cmd)
{
	printf("ARGS:\n");
	for (int i = 0; cmd->av && cmd->av[i]; i++)
		printf("argv[%d]: %s\n", i, cmd->av[i]);

	printf("REDIRS:\n");
	for (t_redirect *r = cmd->redir; r; r = r->next)
		printf("type: %d, file: %s\n", r->type, r->filename);
}
