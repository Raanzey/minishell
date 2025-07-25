#include "../minishell.h"

int	handle_heredocs(t_redirect *redir ,int has_cmd)
{
	int		fd[2];
	int		heredoc_fd;
	char	*line;

	heredoc_fd = -1;;
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
			setup_signals();
			while (1)
			{
				line = readline("> ");
				if ((!line || (!ft_strncmp(line, redir->filename,
							ft_strlen(redir->filename))
						&& line[ft_strlen(redir->filename)] == '\0')) && !has_cmd)
				{
					ft_free();
					break;
				}
				if (!line || (!ft_strncmp(line, redir->filename,
							ft_strlen(redir->filename))
						&& line[ft_strlen(redir->filename)] == '\0'))
				{
					break ;
				}		
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
			}
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
	return has_cmd = 1;
}


