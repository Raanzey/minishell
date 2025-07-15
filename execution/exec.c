#include "../minishell.h"

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
	t_redirect *tmp = redir;

	handle_heredocs(tmp); // sadece heredoc'ları burada işliyoruz

	while (redir)
	{
		int fd = -1;
		if (redir->type == 1)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == 2)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == 3)
			fd = open(redir->filename, O_RDONLY);
		if (redir->type != 4 && fd == -1)
		{
			perror("redir");// hatakodu(56);
			exit(1);//HATAA DURUMUUU//error(56);
		}
		if (redir->type == 3)
			dup2(fd, STDIN_FILENO);
		else if (redir->type == 1 || redir->type == 2)
			dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
		redir = redir->next;
	}
}

static char **convert_env_to_array(t_env *env, int count, int i)
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
		return NULL;
	tmp = env;
	while (tmp)
	{
		joined = ft_strjoin(tmp->key, "=");              // "KEY="
		env_array[i++] = ft_strjoin(joined, tmp->value);   // "KEY=VALUE"
		free(joined); // silinecek
		tmp = tmp->next;
	}
	env_array[i] = NULL; // NULL sonlandır
	return env_array;
}
static void exec_child(t_command *cmd, int prev_fd, int pipe_fd[2], t_env **env_list)
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
	if (!built_in(cmd, env_list))
		exit(1);//ERORR GELCEK
	execve(find_path(cmd->av[0]), cmd->av, convert_env_to_array(*env_list, 0, 0));
	perror("execve");//ERORR GELCEK
	exit(1);//ERORR GELCEK
}

int exec(t_command *cmd, t_env **env_list)
{
	
	int prev_fd = -1;
	int pipe_fd[2];
	pid_t pid;

	g_signal=1;
	if (!cmd->next && is_parent_builtin(cmd))
		return built_in(cmd, env_list);
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
	int status;
	while (wait(&status) > 0)
	{
		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				write(1, "Quit (core dumped)\n", 20);//ERROR DURUMU
			// SIGINT (Ctrl+C) için bir şey yazma, readline kendisi işler
		}
	}
	return 0;
}
