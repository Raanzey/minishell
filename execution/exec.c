#include "../minishell.h"

char	*find_path(char *cmd, t_env *env_list)
{
	char	**paths;
	char	*tmp;
	char	*candidate;
	char	*full_path;
	int		i;

	i = 0;
	tmp = ft_path(env_list); // PATH environment değişkeni
	if (!tmp)
		error("minishell: ", cmd, ERR_CD,127);
	paths = ft_split(tmp, ':');
	// free(tmp);
	while (paths[i])
	{
		candidate = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(candidate, cmd);
		// free(candidate);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		// free(full_path);
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
		if (tmp->value)
			count++;
		tmp = tmp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			joined = ft_strjoin(tmp->key, "=");
			env_array[i++] = ft_strjoin(joined, tmp->value);
			free(joined);
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
static void	handle_redirections(t_command *cmd)
{
	t_redirect	*tmp;
	t_redirect      *redir;
	int			fd;
	int has_cmd;
	
	redir = cmd->redir;
	if (cmd->av && cmd->av[0])
		has_cmd = 1;
	else
		has_cmd = 0;
	tmp = redir; 
	
	handle_heredocs(tmp, has_cmd); // sadece heredoc'ları burada işliyoruz
	
	while (redir) 
	{
		fd = -1;
		//fprintf(stderr, "[REDIR] type: %d, file: %s\n", redir->type, redir->filename);

		if (redir->type == 1)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == 2)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == 3)
			fd = open(redir->filename, O_RDONLY);

		if (redir->type != 4 && fd == -1)
		{
			char *msg;

			msg = ft_strjoin("minishell: ", redir->filename);
			perror(msg);
			// if (fd == 255)
			// 	error("minishell: ", redir->filename, ERR_PERM, 1);
			// else
			// 	error("minishell: ", redir->filename, ERR_CD, 1);
			ft_free();
			exit(1);
		}

		if (redir->type == 3)
		{
			//fprintf(stderr, "[DUP2] Redirecting input from fd %d\n", fd);
			dup2(fd, STDIN_FILENO);
		}
		else if (redir->type == 1 || redir->type == 2)
		{
			//fprintf(stderr, "[DUP2] Redirecting output to fd %d\n", fd);
			dup2(fd, STDOUT_FILENO);
		}

		if (fd != -1 && fd != STDIN_FILENO && fd != STDOUT_FILENO)
			close(fd);

		redir = redir->next;
	}
}
int	has_output_redir(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == 1 || redir->type == 2) // > veya >>
			return (1);
		redir = redir->next;
	}
	return (0);
}
static void	exec_child(t_command *cmd, int prev_fd, int pipe_fd[2],
		t_env **env_list)
{
	char	*path = NULL;

	//fprintf(stderr, "[CHILD] cmd: %s\n", cmd->av ? cmd->av[0] : "(null)");
	if (cmd->redir)
		handle_redirections(cmd);
	else if (prev_fd != -1)
	{
		//fprintf(stderr, "[DUP2] Inheriting prev_fd %d as STDIN\n", prev_fd);
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	setup_signals_main();

	if (!has_output_redir(cmd->redir) &&cmd->next)
	{
		//fprintf(stderr, "[DUP2] Piping STDOUT to pipe write end %d\n", pipe_fd[1]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	// printf("EXEC BUILTIN ONCESI\n");
	int built_code;

	if (cmd->av || cmd->av[0])
	{
		//fprintf(stderr, "[BUILTIN] Executed in child\n");
		built_code = built_in(cmd, env_list);
		if (built_code == 0 || built_code != -1)
		{
			//fprintf(stderr, "[BUILTIN] Executed in child\n");
			ft_free();
			exit(built_code);
		}
	}
	
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
		path = find_path(cmd->av[0], *env_list);
		if (!path)
			error(0, cmd->av[0], ": command not found\n", 127);
	}
 	//fprintf(stderr, "[EXECVE] Executing %s\n", path);
	execve(path, cmd->av, convert_env_to_array(*env_list, 0, 0));
	perror("[EXECVE ERROR]");
	ft_free();
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
		//fprintf(stderr, "[EXEC] New command: %s\n", cmd->av ? cmd->av[0] : "(null)");

		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("[PIPE ERROR]");
			ft_free();
			exit(1);
		}
		discard_signals();
		pid = fork();
		if (pid == -1)
		{
			perror("[FORK ERROR]");
			ft_free();
			exit(1);
		}
		if (pid == 0)
		{
			exec_child(cmd, prev_fd, pipe_fd, env_list);
		}
			// printf("EXECVE SONRASI\n");
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
			if (sig == SIGINT)
				write(1, "\n", 1);
			//fprintf(stderr, "[WAIT] Child killed by signal sonrası %d\n", sig);
		}
	}
	setup_signals_main();
	return (last_exit); // Sonlanan en son child’ın çıkış kodunu döndür
}
		