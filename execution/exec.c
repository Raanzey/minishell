#include "../minishell.h"

char	*find_path(char *cmd)
{
	char	**paths;
	char	*tmp;
	char	*candidate;
	char	*full_path;
	int		i;

	i = 0;
	tmp = ft_path(); // PATH environment değişkeni
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	free(tmp);
	while (paths[i])
	{
		candidate = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(candidate, cmd);
		free(candidate);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
static char	**convert_env_to_array(t_env *env, int count, int i)
{
	t_env	*tmp;
	char	**env_array;
	char	*joined;

	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1)); // +1 NULL için
	if (!env_array)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		joined = ft_strjoin(tmp->key, "=");              // "KEY="
		env_array[i++] = ft_strjoin(joined, tmp->value); // "KEY=VALUE"
		free(joined);                                    // silinecek
		tmp = tmp->next;
	}
	env_array[i] = NULL; // NULL sonlandır
	return (env_array);
}
static void	handle_redirections(t_redirect *redir)
{
	t_redirect	*tmp;
	int			fd;

	tmp = redir;
	handle_heredocs(tmp); // sadece heredoc'ları burada işliyoruz
	while (redir)
	{
		fd = -1;
		if (redir->type == 1)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == 2)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == 3)
			fd = open(redir->filename, O_RDONLY);

		if (redir->type != 4 && fd == -1)
		{
			perror("redir");
			exit(1);
		}
		if (redir->type == 3)
			dup2(fd, STDIN_FILENO);
		else if (redir->type == 1 || redir->type == 2)
			dup2(fd, STDOUT_FILENO);
		if (fd != -1 && fd != STDIN_FILENO && fd != STDOUT_FILENO)
			close(fd);
		redir = redir->next;
	}
}
int	has_input_redir(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == 3 || redir->type == 4) // REDIR_IN veya REDIR_HEREDOC
			return (1);
		redir = redir->next;
	}
	return (0);
}
static void	exec_child(t_command *cmd, int prev_fd, int pipe_fd[2],
		t_env **env_list)
{
	char	*path = NULL;

	if (cmd->redir)
		handle_redirections(cmd->redir);
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (built_in(cmd, env_list) == 0)
		exit(0);
	if (ft_strchr(cmd->av[0], '/'))
	{
		struct stat st;
		if (access(cmd->av[0], F_OK) != 0)
			error(0, cmd->av[0], ": No such file or directory\n", 127);
		else if (access(cmd->av[0], X_OK) != 0)
			error(0, cmd->av[0], ": Permission denied\n", 126);
		else if (stat(cmd->av[0], &st) == 0 && S_ISDIR(st.st_mode))
			error(0, cmd->av[0], ": Is a directory\n", 126);
		else
			path = ft_strdup(cmd->av[0]);
	}
	else
	{
		path = find_path(cmd->av[0]);
		if (!path)
			error(0, cmd->av[0], ": command not found\n", 127);
	}
	execve(path, cmd->av, convert_env_to_array(*env_list, 0, 0));
	perror("execve");
	exit(126);
}


int	exec(t_command *cmd, t_env **env_list)
{
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		last_exit;
	int		sig;

	prev_fd = -1;
	g_signal = 1;
	if (!cmd->redir)
	{
		if (!cmd->av || !cmd->av[0])
			return (0);
	}
	if (!cmd->next && is_parent_builtin(cmd))
		return (built_in(cmd, env_list));
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
			exec_child(cmd, prev_fd, pipe_fd, env_list);

		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			prev_fd = -1;

		cmd = cmd->next;
	}
	last_exit = 0; // Son exit kodunu saklayacak değişken
	// Tüm child process'lerin bitmesini bekle
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		{
			last_exit = WEXITSTATUS(status);
			//fprintf(stderr, "[WAIT] Child exited with %d\n", last_exit);
		}
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			//fprintf(stderr, "[WAIT] Child killed by signal %d\n", sig);
			if (sig != SIGPIPE)
				last_exit = 128 + sig;
			//fprintf(stderr, "[WAIT] Child killed by signal sonrası %d\n", sig);
		}
	}
	return (last_exit); // Sonlanan en son child’ın çıkış kodunu döndür
}
