#include "../minishell.h"

static int	is_delimiter(char *line, char *delim, int has_cmd)
{
	return ((!line || (!ft_strncmp(line, delim, ft_strlen(delim))
				&& line[ft_strlen(delim)] == '\0')) && !has_cmd);
}

static void	handle_heredoc_loop(t_redirect *redir, int *fd, int has_cmd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (is_delimiter(line, redir->filename, has_cmd))
		{
			ft_free();
			break ;
		}
		if (!line || (!ft_strncmp(line, redir->filename,
					ft_strlen(redir->filename))
				&& line[ft_strlen(redir->filename)] == '\0'))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
}

int	handle_heredocs(t_redirect *redir, int has_cmd, int heredoc_fd)
{
	int	fd[2];

	while (redir)
	{
		if (redir->type == 4)
		{
			if (pipe(fd) == -1)
				return (perror("pipe"), ft_free(), exit(1), 1);
			g_signal = 2;
			setup_signals();
			handle_heredoc_loop(redir, fd, has_cmd);
			close(fd[1]);
			if (heredoc_fd != -1)
				close(heredoc_fd);
			heredoc_fd = fd[0];
		}
		redir = redir->next;
	}
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	return (has_cmd = 1);
}

int	has_output_redir(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == 1 || redir->type == 2)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
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
