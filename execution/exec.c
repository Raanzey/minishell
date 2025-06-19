#include "../minishell.h"

static char *ft_path(void)
{
    char *path_env = getenv("PATH");
    if (!path_env)
        exit(1);//ERORR GELCEK
    return strdup(path_env);
}
static char *find_path(char *cmd)
{
	char **paths;
	char *tmp;
	char *candidate;
	char *full_path;
	int i = 0;
	// Eğer komut bir path içeriyorsa doğrudan kontrol et
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		else
			return NULL;
	}// PATH ortam değişkenini al
	tmp = ft_path();
	if (!tmp)
		return NULL;
	paths = ft_split(tmp, ':');
	free(tmp);
	while (paths[i])
	{
		candidate = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(candidate, cmd);
		free(candidate);
		if (access(full_path, X_OK) == 0)
			return full_path;// paths dizisini free etmeyi unutma (ileride)
		free(full_path);
		i++;
	}// paths dizisini burada da free etmeyi unutma (ileride)
	return NULL;
}
static void handle_redirections(t_redirect *redir)
{
	while (redir)
	{
		int fd = -1;
		if (redir->type == 1)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == 2)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == 3)
			fd = open(redir->filename, O_RDONLY);
		if (fd == -1)
		{
			perror("redir");//ERORR GELCEK
			exit(1);//ERORR GELCEK
		}
		if (redir->type == 3)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}

static void exec_child(t_command *cmd, int prev_fd, int pipe_fd[2], char **env)
{
	if (cmd->redir)							//FONKSİYONDKİ DEĞİŞKEN SAYISINA DİKKAT
		handle_redirections(cmd->redir);
	if (prev_fd != -1)
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
	if (!built_in(cmd))
		exit(1);//ERORR GELCEK
	execve(find_path(cmd->av[0]), cmd->av, env);
	perror("execve");//ERORR GELCEK
	exit(1);//ERORR GELCEK
}

int exec(t_command *cmd, char **env)
{
	int prev_fd = -1;
	int pipe_fd[2];
	pid_t pid;

	if (!cmd->next && is_parent_builtin(cmd))
		return built_in(cmd);
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");//ERORR GELCEK
			exit(1);//ERORR GELCEK
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");//ERORR GELCEK
			exit(1);//ERORR GELCEK
		}
		if (pid == 0)
			exec_child(cmd, prev_fd, pipe_fd, env);
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
	while (wait(NULL) > 0);
	return 0;
}
