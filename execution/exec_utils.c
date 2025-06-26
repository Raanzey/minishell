#include "../minishell.h"

char *ft_path(void)
{
    char *path_env = getenv("PATH");
    if (!path_env)
        exit(1);//ERORR GELCEK
    return strdup(path_env);
}

void	handle_heredoc(const char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)) && line[ft_strlen(delimiter)] == '\0')
			break;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}