/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:01:38 by musisman          #+#    #+#             */
/*   Updated: 2025/07/28 18:53:46 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirections(t_command *cmd)
{
	t_redirect	*redir;
	int			fd;
	int			has_cmd;

	redir = cmd->redir;
	has_cmd = (cmd->av && cmd->av[0]);
	handle_heredocs(redir, has_cmd, -1);
	while (redir)
	{
		
		fd = open_redir_fd(redir);
		if ((redir->type == 1 || redir->type == 2 || redir->type == 3)
			&& fd == -1)
		{
			err_exp(redir->filename, 0, 1, 1);
			ft_free();
			exit(1);
		}
		dup_redir_fd(redir, fd);
		redir = redir->next;
	}
}

void	exec_child(t_command *cmd, int prev_fd, int pipe_fd[2],
		t_env **env_list)
{
	char	*path;
	int		built_code;

	child_redirect(cmd, prev_fd, pipe_fd);
	setup_signals();
	if (cmd->av || cmd->av[0])
	{
		built_code = built_in(cmd, env_list);
		if (built_code == 0 || built_code != -1)
		{
			ft_free();
			exit(built_code);
		}
	}
	path = handle_path(cmd, env_list);
	execve(path, cmd->av, convert_env_to_array(*env_list, 0, 0, NULL));
	ft_free();
	exit(err_exp("execve: ", 0, 1, 126));
}

static void	create_child_or_die(t_command *cmd, int prev_fd, int pipe_fd[2],
		t_env **env_list)
{
	pid_t	pid;

	discard_signals();
	g_signal = 1;
	pid = fork();
	if (pid == -1)
	{
		ft_free();
		exit(err_exp("fork: ", 0, 1, 1));
	}
	if (pid == 0)
		exec_child(cmd, prev_fd, pipe_fd, env_list);
}

static int	wait_all_child(void)
{
	int	status;
	int	last_exit;
	int	sig;

	last_exit = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig != SIGPIPE)
				last_exit = 128 + sig;
			if (sig == SIGINT)
				write(1, "\n", 1);
		}
	}
	setup_signals();
	return (last_exit);
}

int	exec(t_command *cmd, t_env **env_list)
{
	int	prev_fd;
	int	pipe_fd[2];

	prev_fd = -1;
	if (!cmd)
		return (0);
	if (!cmd->next && is_parent_builtin(cmd))
		return (built_in(cmd, env_list));
	while (cmd)
	{
		setup_pipe_or_die(cmd, pipe_fd);
		create_child_or_die(cmd, prev_fd, pipe_fd, env_list);
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
	return (wait_all_child());
}
