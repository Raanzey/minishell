#include "../minishell.h"

char *get_env_value(t_env *env, const char *key)
{
	if (!env->value)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value); // NULL olabilir ama burada strdup yapmana gerek yok
		env = env->next;
	}
	return (0);
}

char	*ft_path(t_env *env)
{
	char *path_env;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL); // Komutların PATH olmadan bulunamaması hatası
	return (ft_strdup(path_env));
}

void	handle_heredocs(t_redirect *redir ,int has_cmd)
{
	int		fd[2];
	int		heredoc_fd;
	char	*line;

	heredoc_fd = -1;
	// signal(SIGINT, handle_sigint_exec);
	// signal(SIGQUIT,handle_sigint_exec);
	while (redir)
	{
		if (redir->type == 4)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				ft_free();
				exit(1);
			}
			g_signal = 2;
			setup_signals(); // readline için doğru signal davranışı
			while (1)
			{
				line = readline("> ");
				if ((!line || (!ft_strncmp(line, redir->filename,
							ft_strlen(redir->filename))
						&& line[ft_strlen(redir->filename)] == '\0')) && !has_cmd)
				{
					ft_free();
				}
				if (!line || (!ft_strncmp(line, redir->filename,
							ft_strlen(redir->filename))
						&& line[ft_strlen(redir->filename)] == '\0'))
				{
					
					break ;
				}		
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				// free(line);
			}
			// free(line);
			close(fd[1]);
			if (heredoc_fd != -1)
				close(heredoc_fd);
			heredoc_fd = fd[0]; // sadece son heredoc'un pipe'ı tutulur
		}
		redir = redir->next;
	}
	if (heredoc_fd != -1)
	{
        dup2(heredoc_fd, STDIN_FILENO);
        close(heredoc_fd);
    }
}

int	is_numeric(const char *str)
{
	int i = 0;

	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}