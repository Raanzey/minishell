#include "../minishell.h"

int	error_value(int num)
{
	return (num); // :D
}

char	*ft_path(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		exit(1); // ERORR GELCEK
	return (strdup(path_env));
}

void	handle_heredocs(t_redirect *redir)
{
	int		fd[2];
	int		heredoc_fd;
	char	*line;

	heredoc_fd = -1;
	g_signal = 2;
	while (redir)
	{
		if (redir->type == 4)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(1);
			}
			while (1)
			{
				line = readline("> ");
				if (!line || (!ft_strncmp(line, redir->filename,
							ft_strlen(redir->filename))
						&& line[ft_strlen(redir->filename)] == '\0'))
					break ;
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				free(line);
			}
			free(line);
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

// int handle_heredocs(t_redirect *redir)
// {
//     int fd[2];
//     int heredoc_fd = -1;
//     char *line;

//     g_signal = 2;
//     while (redir)
//     {
//         if (redir->type == 4)
//         {
//             if (pipe(fd) == -1)
//             {
//                 perror("pipe");
//                 exit(1);
//             }
//             while (1)
//             {
//                 line = readline("> ");
//                 if (!line || (!ft_strncmp(line, redir->filename, ft_strlen(redir->filename)) && line[ft_strlen(redir->filename)] == '\0'))
//                     break;
//                 write(fd[1], line, ft_strlen(line));
//                 write(fd[1], "\n", 1);
//                 free(line);
//             }
//             free(line);
//             close(fd[1]);
//             if (heredoc_fd != -1)
//                 close(heredoc_fd);
//             heredoc_fd = fd[0];
//         }
//         redir = redir->next;
//     }
//     return heredoc_fd;
// }


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