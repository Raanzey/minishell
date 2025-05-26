#include "../minishell.h"

t_command	*new_command(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	is_redir(char *s)
{
	return (!ft_strncmp(s, "<", 2) || !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3) || !ft_strncmp(s, ">>", 3));
}

t_redirect	*create_redirect(char *op, char *file)
{
	t_redirect *r = malloc(sizeof(t_redirect));
	if (!r || !file)
		return (NULL);
	r->filename = ft_strdup(file);
	r->next = NULL;
	if (!ft_strncmp(op, "<<", 3))
		r->type = 4;
	else if (!ft_strncmp(op, ">>", 3))
		r->type = 2;
	else if (!ft_strncmp(op, "<", 2))
		r->type = 3;
	else
		r->type = 1;
	return (r);
}

void	add_redirect(t_command *cmd, t_redirect *r)
{
	t_redirect *cur = cmd->redir;
	if (!cur)
		cmd->redir = r;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = r;
	}
}

void	add_arg(t_command *cmd, char *word)
{
	int i = 0;
	while (cmd->av && cmd->av[i])
		i++;
	char **new = ft_calloc(i + 2, sizeof(char *));
	for (int j = 0; j < i; j++)
		new[j] = cmd->av[j];
	new[i] = ft_strdup(word);
	new[i + 1] = NULL;
	free(cmd->av);
	cmd->av = new;
}

t_command *parser(char **tokens)
{
	t_command *first = NULL;
	t_command *cur = NULL;
	size_t i = 0;

	while (tokens[i])
	{
		t_command *cmd = new_command();
		if (!first)
			first = cmd;
		else
			cur->next = cmd;
		cur = cmd;
		while (tokens[i] && ft_strncmp(tokens[i], "|", 2))
		{
			if (is_redir(tokens[i]))
			{
				if (!tokens[i + 1])
					return (NULL); // syntax error
				t_redirect *r = create_redirect(tokens[i], tokens[i + 1]);
				add_redirect(cmd, r);
				i += 2;
			}
			else
			{
				add_arg(cmd, tokens[i]);
				i++;
			}
		}
		if (tokens[i] && !ft_strncmp(tokens[i], "|", 2))
			i++;
	}
	return (first);
}







// size_t	ft_word(t_command *cmd, char *token)
// {
// 	int i = 0;

// 	while (cmd->av && cmd->av[i])
// 		i++;

// 	char **new_argv = ft_calloc(i + 2, sizeof(char *));
// 	if (!new_argv)
// 		return (0);
// 	for (int j = 0; j < i; j++)
// 		new_argv[j] = cmd->av[j];
// 	new_argv[i] = ft_strdup(token);
// 	new_argv[i + 1] = NULL;
// 	free(cmd->av);
// 	cmd->av = new_argv;
// 	return (1);
// }

// size_t	ft_redirect(t_command *cmd, char **tokens, size_t i)
// {
// 	t_redirect *redir;

// 	if (!tokens[i + 1])
// 	{
// 		printf("syntax error: missing filename after redirection\n");
// 		return (0); // ya da hata kodu döndür
// 	}

// 	redir = malloc(sizeof(t_redirect));
// 	if (!redir)
// 		return (0);
// 	if (ft_strncmp(tokens[i], "<<", 3) == 0)
// 		redir->type = 4;
// 	else if (ft_strncmp(tokens[i], ">>", 3) == 0)
// 		redir->type = 2;
// 	else if (ft_strncmp(tokens[i], "<", 2) == 0)
// 		redir->type = 3;
// 	else if (ft_strncmp(tokens[i], ">", 2) == 0)
// 		redir->type = 1;
// 	else
// 	{
// 		free(redir);
// 		return (0);
// 	}

// 	redir->filename = ft_strdup(tokens[i + 1]);
// 	redir->next = NULL;

// 	// Redir zincirine ekle
// 	if (!cmd->redir)
// 		cmd->redir = redir;
// 	else
// 	{
// 		t_redirect *tmp = cmd->redir;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = redir;
// 	}
// 	return (1); // kaç token yediğini belirtmek için
// }

// void	free_command(t_command *cmd)
// {
// 	int i = 0;

// 	if (!cmd)
// 		return;
// 	if (cmd->av)
// 	{
// 		while (cmd->av[i])
// 			free(cmd->av[i++]);
// 		free(cmd->av);
// 	}
// 	t_redirect *r = cmd->redir;
// 	while (r)
// 	{
// 		t_redirect *tmp = r;
// 		r = r->next;
// 		free(tmp->filename);
// 		free(tmp);
// 	}
// 	free(cmd);
// }

// t_command	*parser(char *input)
// {
// 	t_command	*cmd;
// 	char		**tokens;
// 	size_t		i;
// 	// int			consumed;

// 	tokens = tokenizer(input);
//         cmd = NULL;
// 	if (!tokens)
// 		return (NULL);
//         i = -1;
//         while (tokens[++i])
//                 printf("%ld. %s\n", i, tokens[i]);
        
// 	// cmd = malloc(sizeof(t_command));
// 	// if (!cmd)
// 	// 	return (NULL);
// 	// cmd->av = NULL;
// 	// cmd->redir = NULL;
// 	// cmd->next = NULL;

// 	// i = 0;
// 	// while (tokens[i])
// 	// {
// 	// 	if (ft_strncmp(tokens[i], "|", 2) == 0)
// 	// 		break ; // pipe desteği için ileride yeni t_command oluşturulacak

// 	// 	if (ft_strncmp(tokens[i], "<", 2) == 0
// 	// 		|| ft_strncmp(tokens[i], ">", 2) == 0
// 	// 		|| ft_strncmp(tokens[i], "<<", 3) == 0
// 	// 		|| ft_strncmp(tokens[i], ">>", 3) == 0)
// 	// 	{
// 	// 		consumed = ft_redirect(cmd, tokens, i);
// 	// 		if (consumed == 0)
// 	// 		{
// 	// 			printf("Parsing error: missing filename after redirection\n");
// 	// 			// Burada sadece parser kısmı olduğundan input'u main'de free'le
// 	// 			free_command(cmd); // bunu yazmadıysan beraber yazarız
// 	// 			return (NULL);
// 	// 		}
// 	// 		i += consumed;
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		ft_word(cmd, tokens[i]);
// 	// 		i++;
// 	// 	}
// 	// }
// 	return (cmd);
// }


void	print_cmd(t_command *cmd)
{
	int			i;
	int			num = 1;
	t_redirect	*r;

	while (cmd)
	{
		printf("=== COMMAND %d ===\n", num++);
		printf("ARGS:\n");
		i = -1;
		while (cmd->av && cmd->av[++i])
			printf("av[%d]: %s\n", i, cmd->av[i]);

		printf("REDIRS:\n");
		r = cmd->redir;
		while (r)
		{
			printf("type: %d, file: %s\n", r->type, r->filename);
			r = r->next;
		}
		cmd = cmd->next;
	}
}

