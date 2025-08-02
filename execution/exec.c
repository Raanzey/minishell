/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:01:38 by musisman          #+#    #+#             */
/*   Updated: 2025/08/02 15:11:31 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_redirect(t_command *cmd, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (!has_output_redir(cmd->redir) && cmd->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (cmd->redir)
		handle_redirections(cmd);
	if (cmd->next || prev_fd != -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	exec_child(t_command *cmd, int prev_fd, int pipe_fd[2],
		t_env **env_list)
{
	char	*path;
	int		built_code;

	child_redirect(cmd, prev_fd, pipe_fd);
	setup_signals();
	if (cmd->av && cmd->av[0])
	{
		built_code = built_in(cmd, env_list, -1);
		if (built_code == 0 || built_code != -1)
			free_and_exit(built_code);
	}
	else
		free_and_exit(0);
	path = handle_path(cmd, env_list);
	execve(path, cmd->av, convert_env_to_array(*env_list, 0, 0, NULL));
	free_and_exit(err_exp("execve: ", 0, 1, 126));
}

static void	create_child_or_die(t_command *cmd, int prev_fd, int pipe_fd[2],
		t_env **env_list)
{
	pid_t	pid;

	discard_signals();
	g_signal = 1;
	pid = fork();
	if (pid == -1)
		free_and_exit(err_exp("fork: ", 0, 1, 1));
	if (pid == 0)
		exec_child(cmd, prev_fd, pipe_fd, env_list);
}

int	preprocess_heredocs(t_command *cmd)
{
	t_command	*cur;
	int			res;

	cur = cmd;
	while (cur)
	{
		if (contains_heredoc(cur->redir))
		{
			res = handle_heredocs(cur->redir);
			if (res != 0)
				return (res);
		}
		cur = cur->next;
	}
	return (0);
}

int	exec(t_command *cmd, t_env **env_list, t_status *status)
{
	int	pipe_fd[2];

	if (!cmd)
		return (0);
	status->heredoc_status = preprocess_heredocs(cmd);
	if (status->heredoc_status != 0)
		return (status->heredoc_status);
	if (!cmd->next && is_parent_builtin(cmd))
		return (built_in(cmd, env_list, status->exit_code));
	while (cmd)
	{
		setup_pipe_or_die(cmd, pipe_fd);
		create_child_or_die(cmd, status->prev_fd, pipe_fd, env_list);
		if (status->prev_fd != -1)
			close(status->prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			status->prev_fd = pipe_fd[0];
		}
		else
			status->prev_fd = -1;
		cmd = cmd->next;
	}
	return (wait_all_child());
}
