#include "../minishell.h"

void	setup_pipe_or_die(t_command *cmd, int pipe_fd[2])
{
	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("[PIPE ERROR]");
		ft_free();
		exit(1);
	}
}

int	open_redir_fd(t_redirect *redir)
{
	if (redir->type == 1)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == 2)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (redir->type == 3)
		return (open(redir->filename, O_RDONLY));
	return (-1);
}

void	dup_redir_fd(t_redirect *redir, int fd)
{
	if (redir->type == 3)
		dup2(fd, STDIN_FILENO);
	else if (redir->type == 1 || redir->type == 2)
		dup2(fd, STDOUT_FILENO);
	if (fd != -1 && fd != STDIN_FILENO && fd != STDOUT_FILENO)
		close(fd);
}

void	child_redirect(t_command *cmd, int prev_fd, int pipe_fd[2])
{
	if (cmd->redir)
		handle_redirections(cmd);
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (!has_output_redir(cmd->redir) && cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

char	*handle_path(t_command *cmd, t_env **env_list)
{
	struct stat	st;
	char		*path;

	if (ft_strchr(cmd->av[0], '/'))
	{
		if (access(cmd->av[0], F_OK) != 0)
			error(0, cmd->av[0], ": No such file or directory\n", 127);
		else if (access(cmd->av[0], X_OK) != 0)
			error(0, cmd->av[0], ": Permission denied\n", 126);
		else if (stat(cmd->av[0], &st) == 0 && S_ISDIR(st.st_mode))
			error(0, cmd->av[0], ": Is a directory\n", 126);
		else
			return (ft_strdup(cmd->av[0]));
	}
	else
	{
		path = find_path(cmd->av[0], *env_list);
		if (!path)
			error(0, cmd->av[0], ": command not found\n", 127);
		return (path);
	}
	return (NULL);
}
